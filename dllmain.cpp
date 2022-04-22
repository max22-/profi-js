#include "dll.h"
extern "C" {
  #include <mujs.h>
}

js_State *J;

//Eingang 0 = CLK, Eingang 1 = RST
const unsigned char CLK = 0;
const unsigned char RST = 1;
  
//Bezeichnung für User-variabelen
const unsigned char CLK_OLD = 0;
const unsigned char RST_OLD = 1;
const unsigned char COUNT = 2;

TCHAR script_path[MAX_PATH];

void info(const char *title, const char* msg)
{
  MessageBox(NULL,TEXT(msg),TEXT(title), MB_OK);
}

void error(const char *title, const char* msg)
{
  MessageBox(NULL,TEXT(msg),TEXT(title), MB_OK | MB_ICONERROR);
}

/* MuJS functions */
static void alert(js_State *J)
{
	const char *msg = js_tostring(J, 1);
	info("Javascript", msg);
	js_pushundefined(J);
}

int load_script()
{
  if(js_dofile(J, script_path) != 0) {
    char msg[1024];
    snprintf(msg, sizeof(msg), "Failed to load %s", script_path);
    error("Javascript", msg);
    return 0;
  }
  return 1;
}

DLLEXPORT unsigned char _stdcall NumInputs()
{
  int res;
  js_getglobal(J, "NumInputs");
  js_pushnull(J);
  if(js_pcall(J, 0)) {
    error("Javascript", "Error while calling NumInputs()");
    js_pop(J, 1);
    return 0;
  }
  res = js_tonumber(J, -1);
  js_pop(J, 1);
  return res;
}
  
 
DLLEXPORT unsigned char _stdcall NumOutputs()
{
  int res;
  js_getglobal(J, "NumOutputs");
  js_pushnull(J);
  if(js_pcall(J, 0)) {
    error("Javascript", "Error while calling NumOutputs()");
    js_pop(J, 1);
    return 0;
  }
  res = js_tonumber(J, -1);
  js_pop(J, 1);
  return res;
}
  
//Aufruf von PROFILAB, liest die Namen der Eingänge 
DLLEXPORT void _stdcall GetInputName(unsigned char Channel,unsigned char *Name)
{
  js_getglobal(J, "GetInputName");
  js_pushnull(J);
  js_pushnumber(J, Channel);
  if(js_pcall(J, 1)) {
    error("Javascript", "Error while calling GetInputName()");
    js_pop(J, 1);
    return;
  }
  strcpy((char*)Name, js_tostring(J, -1));
  js_pop(J, 1);
}
  
//Aufruf von PROFILAB, liest die Namen der Eingänge 
DLLEXPORT void _stdcall GetOutputName(unsigned char Channel,unsigned char *Name)
{
  js_getglobal(J, "GetOutputName");
  js_pushnull(J);
  js_pushnumber(J, Channel);
  if(js_pcall(J, 1)) {
    error("Javascript", "Error while calling GetOutputName()");
    js_pop(J, 1);
    return;
  }
  strcpy((char*)Name, js_tostring(J, -1));
  js_pop(J, 1);
}
  
//Aufruf von PROFILAB, setzt bei Programmstart den "Counter"auf "0"+ setzt alle Ausgaenge zurueck
DLLEXPORT void _stdcall CSimStart(double *PInput, double *POutput, double *PUser)
{
  load_script();
  /*
      int i;
  
      PUser[COUNT] = 0;               //"Counter" ruecksetzen
      for (i = 0; i < outputs; i++)   //Alle Ausgaenge ruecksetzen
                POutput[i] = 0;
  */
}
  
//Aufruf von PROFILAB,hier steht die eigentliche Funktion der DLL
//
DLLEXPORT void _stdcall CCalculate(double *PInput, double *POutput, double *PUser)
{
  /*
      int i, iCount;
  
      if (PInput[RST] < 2.5) // RST Eingang LOW?
      {
            if (PUser[RST_OLD] > 2.5) //fallende Flanke von RST?
            {
                  PUser[COUNT] = 0; //"Counter" ruecksetzen
                  for (i = 0; i < outputs; i++)  //alle Ausgaenge ruecksetzen
                        POutput[i] = 0;
            }
      }
      PUser[RST_OLD] = PInput[RST]; //Zustand von Eingang RST für naechsten Aufruf speichern
  
  
      if (PInput[CLK] > 2.5)  //Eingang CLK high?
      {
            if (PUser[CLK_OLD] < 2.5) //steigende Flanke von CLK?
            {
                    PUser[COUNT] += 1; //"Counter" inkrementieren
                        if (PUser[COUNT] > 255)      PUser[COUNT] = 0; //überprüfen auf Ueberlauf
						                                               //8-Bit max 256
                        iCount = (int)PUser[COUNT];  //von double nach int
						POutput[8] = iCount;
                        //die entsprechenden Ausgaenge binaer setzen
						//low = 0, high = 5
                        if ((iCount & 1))   POutput[0] = 5; else POutput[0] = 0;
                        if ((iCount & 2))   POutput[1] = 5; else POutput[1] = 0;
                        if ((iCount & 4))   POutput[2] = 5; else POutput[2] = 0;
                        if ((iCount & 8))   POutput[3] = 5; else POutput[3] = 0;
                        if ((iCount & 16))  POutput[4] = 5; else POutput[4] = 0;
                        if ((iCount & 32))  POutput[5] = 5; else POutput[5] = 0;
                        if ((iCount & 64))  POutput[6] = 5; else POutput[6] = 0;
                        if ((iCount & 128)) POutput[7] = 5; else POutput[7] = 0;
            }
			      }
      PUser[CLK_OLD] = PInput[CLK]; // Wert des Eigangs CLK für naechsten Aufruf speichern
  */
}
  
// Aufruf von PROFILAB, wird beim Simulations-Stop aufgerufen
DLLEXPORT void _stdcall CSimStop(double *PInput, double *POutput, double *PUser)
{
  
}
// erforderlich für MessageBox
int WINAPI WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szComdLine, int iCmdShow);  
//Aufruf von PROFILAB, wird im Configurations-Menü aufgerufen

DLLEXPORT void _stdcall CConfigure(double *PUser)
{
  info("Javascript", "Reloading script");
  load_script();
    js_getglobal(J, "CConfigure");
    js_pushnull(J);
    if(js_pcall(J, 0)) {
      error("Javascript", "Error while calling CConfigure()");
      js_pop(J, 1);
      return;
    }
    js_pop(J, 1);
    MessageBox(NULL,TEXT("nichts zu configurieren"),TEXT("Config"), MB_OK);
}





BOOL APIENTRY DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
  char msg[256];
  DWORD len;
    switch (reason)
    {
      case DLL_PROCESS_ATTACH:
	
	J = js_newstate(NULL, NULL, JS_STRICT);
	js_newcfunction(J, alert, "alert", 1);
	js_setglobal(J, "alert");
	
	len = GetModuleFileName( hInst, script_path, MAX_PATH );
	while(script_path[len] != '.' && len > 0) len--;
	if(len > 0) {
	  script_path[len+1] = 0;
	  strcat(script_path, "js");
	  info("test", script_path);
	  load_script();
	}
	else error("DLL", "Failed to find DLL path");
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
