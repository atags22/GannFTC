#ifndef AUTOCHOSER
#define AUTOCHOSER
#endif

bool color;
bool side;
int path;
long waittime = 0;

void disppath(int line){
  if (path == 1){
    nxtDisplayTextLine(line, "knock crates park");\
  }
  if (path == 2){
    nxtDisplayTextLine(line, "bowling ball park");
  }
  if (path == 3){
    nxtDisplayTextLine(line, "Wrath of G-d");
  }
}
void decidepgm(){
  eraseDisplay();
  nxtDisplayTextLine(1,"Choose Red or Blue");
  nxtDisplayTextLine(2,"Red");
  color = REDCL;
  while( nNxtButtonPressed != kEnterButton){
    if ( nNxtButtonPressed == kLeftButton){
      nxtDisplayTextLine(2,"Blue");
      color = BLUECL;
    }
    else if (nNxtButtonPressed == kRightButton){
      nxtDisplayTextLine(2,"Red");
      color = REDCL;
    }
  }
  while (nNxtButtonPressed == kEnterButton){}
  nxtDisplayTextLine(1,"Right or left");
  nxtDisplayTextLine(2,"Right");
  side = RIGHTSD;
  while(nNxtButtonPressed != kEnterButton){
    if (nNxtButtonPressed == kRightButton){
      nxtDisplayTextLine(2,"Right");
      side = RIGHTSD;
    }
    if (nNxtButtonPressed == kLeftButton){
      nxtDisplayTextLine(2,"Left");
      side = LEFTSD;
    }
  }
  eraseDisplay();
  while (nNxtButtonPressed == kEnterButton){}
  path = 1;
  nxtDisplayTextLine(1, "Choose a plan");
  nxtDisplayTextLine(3, "1:knock crates park");
  nxtDisplayTextLine(4, "2:bowling ball park");
  nxtDisplayTextLine(5, "3:Wrath of G-d");
  disppath(2);
  while (nNxtButtonPressed != kEnterButton){
    if (nNxtButtonPressed == kRightButton && path < 3){
      path++;
      nxtDisplayTextLine(2,"plan: " +path);
      wait1Msec(400);
    }
    if (nNxtButtonPressed == kLeftButton && path > 1 ){
      path--;
      nxtDisplayTextLine(2, "plan: " +path);
      wait1Msec(400);
    }
    nxtDisplayTextLine(2,"plan: " +path);
  }
  eraseDisplay();
  while (nNxtButtonPressed == kEnterButton){}
  waittime = 0;
  while (nNxtButtonPressed != kEnterButton){
    nxtDisplayTextLine(1, "waiting:"+waittime + "msecs");
    if (nNxtButtonPressed == kRightButton){
      waittime += 10;
      wait1Msec(10);
    }
    if (nNxtButtonPressed == kLeftButton && waittime > 0){
      waittime-=10;
      wait1Msec(10);
    }
  }
  eraseDisplay();

  while (nNxtButtonPressed == kEnterButton){}
  eraseDisplay();
  nxtDisplayTextLine(1,"Confirm selections");
nxtDisplayTextLine(2,"Our color is "+ (color == REDCL ? "red" : "blue"));
nxtDisplayTextLine(3,"We are  "+ (side == RIGHTSD ? "right": "left"));
  disppath(4);
  nxtDisplayTextLine(5, "wait" + waittime + "msecs");
  nxtDisplayTextLine(6, "Press center button");
  while(nNxtButtonPressed !=kEnterButton){}
  eraseDisplay();
}
