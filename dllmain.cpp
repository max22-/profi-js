#include "builtin_script.h"
#include "dll.h"
#include <mujs.h>
#include <stdarg.h>

js_State *J;
TCHAR script_path[MAX_PATH];

static double *GInput = NULL, *GOutput = NULL, *GUser = NULL;

#define SETUP()                                                                \
  {                                                                            \
    load_script();                                                             \
    GInput = PInput;                                                           \
    GOutput = POutput;                                                         \
    GUser = PUser;                                                             \
  }
#define SETUP_CALC()                                                           \
  {                                                                            \
    GInput = PInput;                                                           \
    GOutput = POutput;                                                         \
    GUser = PUser;                                                             \
  }
#define SETUP_1()                                                              \
  {                                                                            \
    load_script();                                                             \
    GUser = PUser;                                                             \
  }
#define TEARDOWN()                                                             \
  {                                                                            \
    GInput = NULL;                                                             \
    GOutput = NULL;                                                            \
    GUser = NULL;                                                              \
  }

static void msgbox(const char *title, UINT utype, const char *msg, ...) {
  char buf[1024];
  va_list args;
  va_start(args, msg);
  vsnprintf(buf, sizeof(buf), msg, args);
  va_end(args);
  MessageBox(NULL, TEXT(buf), TEXT(title), utype);
}

#define info(title, msg, ...) msgbox(title, MB_OK, msg, ##__VA_ARGS__)
#define error(title, msg, ...)                                                 \
  msgbox(title, MB_OK | MB_ICONERROR, msg, ##__VA_ARGS__)

/* MuJS functions */

static void muJSPanic(js_State *J) {
  error("Javascript", "%s", js_tostring(J, -1));
}

static void muJSReport(js_State *J, const char *message) {
  info("Javascript", "%s", message);
}

static void alert(js_State *J) {
  if (js_isundefined(J, 1))
    info("Javascript", "undefined");
  else if (js_isnull(J, 1))
    info("Javascript", "null");
  else if (js_isboolean(J, 1)) {
    if (js_toboolean(J, 1))
      info("Javascript", "true");
    else
      info("Javascript", "false");
  } else if (js_isnumber(J, 1))
    info("Javascript", "%f", js_tonumber(J, 1));
  else if (js_isstring(J, 1))
    info("Javascript", "%s", js_tostring(J, 1));
  js_pop(J, 1);
  js_pushundefined(J);
}

static void pinput(js_State *J) {
  char buf[256];
  if (!js_isstring(J, 1)) {
    js_pop(J, 1);
    js_typeerror(J, "pinput: expected string");
    js_pushundefined(J);
    return;
  }
  const char *name = js_tostring(J, 1);
  info("javascript", "name=%s", name);
  snprintf(buf, sizeof(buf), "inputs.indexOf(\"%s\")");
  js_dostring(J, buf);
  int pin = js_tointeger(J, -1);
  js_pop(J, 1);
  if (pin == -1) {
    js_error(J, "Input \"%s\" not found", name);
    js_pushundefined(J);
    return;
  }
  if (GInput != NULL)
    js_pushnumber(J, GInput[pin]);
  else {
    js_error(J, "DLL error (GInput == NULL)");
    js_pushundefined(J);
  }
}

static void poutput(js_State *J) {}

static void puser_set(js_State *J) {}

static void puser_get(js_State *J) {}

static int load_script() {
  if (js_dofile(J, script_path) != 0) {
    error("Javascript", "Failed to load %s", script_path);
    return 0;
  }
  return 1;
}

DLLEXPORT unsigned char _stdcall NumInputs() {
  int res;
  js_getglobal(J, "NumInputs");
  js_pushnull(J);
  if (js_pcall(J, 0)) {
    error("Javascript", "Error while calling NumInputs()");
    js_pop(J, 1);
    return 0;
  }
  res = js_tonumber(J, -1);
  js_pop(J, 1);
  return res;
}

DLLEXPORT unsigned char _stdcall NumOutputs() {
  int res;
  js_getglobal(J, "NumOutputs");
  js_pushnull(J);
  if (js_pcall(J, 0)) {
    error("Javascript", "Error while calling NumOutputs()");
    js_pop(J, 1);
    return 0;
  }
  res = js_tonumber(J, -1);
  js_pop(J, 1);
  return res;
}

DLLEXPORT void _stdcall GetInputName(unsigned char Channel,
                                     unsigned char *Name) {
  js_getglobal(J, "GetInputName");
  js_pushnull(J);
  js_pushnumber(J, Channel);
  if (js_pcall(J, 1)) {
    error("Javascript", "Error while calling GetInputName()");
    js_pop(J, 1);
    return;
  }
  strcpy((char *)Name, js_tostring(J, -1));
  js_pop(J, 1);
}

DLLEXPORT void _stdcall GetOutputName(unsigned char Channel,
                                      unsigned char *Name) {
  js_getglobal(J, "GetOutputName");
  js_pushnull(J);
  js_pushnumber(J, Channel);
  if (js_pcall(J, 1)) {
    error("Javascript", "Error while calling GetOutputName()");
    js_pop(J, 1);
    return;
  }
  strcpy((char *)Name, js_tostring(J, -1));
  js_pop(J, 1);
}

DLLEXPORT void _stdcall CSimStart(double *PInput, double *POutput,
                                  double *PUser) {
  SETUP();

  js_getglobal(J, "CSimStart");
  js_pushnull(J);
  if (js_pcall(J, 0))
    error("Javascript", "Error while calling CSimStart() : %s\n",
          js_trystring(J, -1, "Error"));
  js_pop(J, 1);

  TEARDOWN();
}

DLLEXPORT void _stdcall CCalculate(double *PInput, double *POutput,
                                   double *PUser) {
  SETUP_CALC();
  TEARDOWN();
}

DLLEXPORT void _stdcall CSimStop(double *PInput, double *POutput,
                                 double *PUser) {
  SETUP();
  TEARDOWN();
}
// Required for MessageBox
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR szComdLine, int iCmdShow);

DLLEXPORT void _stdcall CConfigure(double *PUser) {
  SETUP_1();
  js_getglobal(J, "CConfigure");
  js_pushnull(J);

  if (js_pcall(J, 0))
    error("Javascript", "Error while calling CConfigure() : %s\n",
          js_trystring(J, -1, "Error"));
  js_pop(J, 1);
  TEARDOWN();
}

BOOL APIENTRY DllMain(HINSTANCE hInst /* Library instance handle. */,
                      DWORD reason /* Reason this function is being called. */,
                      LPVOID reserved /* Not used. */) {
  char msg[256];
  DWORD len;
  switch (reason) {
  case DLL_PROCESS_ATTACH:

    J = js_newstate(NULL, NULL, JS_STRICT);
    js_atpanic(J, muJSPanic);
    js_setreport(J, muJSReport);
    js_newcfunction(J, alert, "alert", 1);
    js_setglobal(J, "alert");
    js_newcfunction(J, pinput, "pinput", 1);
    js_setglobal(J, "pinput");
    js_newcfunction(J, poutput, "poutput", 2);
    js_setglobal(J, "poutput");
    js_newcfunction(J, puser_set, "puser_set", 2);
    js_setglobal(J, "PUser_set");
    js_newcfunction(J, puser_get, "puser_get", 1);
    js_setglobal(J, "PUser_get");
    js_dostring(J, builtin_script);

    len = GetModuleFileName(hInst, script_path, MAX_PATH);
    while (script_path[len] != '.' && len > 0)
      len--;
    if (len > 0) {
      script_path[len + 1] = 0;
      strcat(script_path, "js");
      load_script();
    } else
      error("DLL", "Failed to find DLL path");
    break;

  case DLL_PROCESS_DETACH:
    info("Javascript", "Detach");
    js_freestate(J);
    break;

  case DLL_THREAD_ATTACH:
    break;

  case DLL_THREAD_DETACH:
    break;
  }
  return TRUE;
}
