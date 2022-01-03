const bord1 = document.getElementById('bord1');
const mapW = 16;
const mapH = 8;
const ctx1 = bord1.getContext('2d');

const tileW = 40, tileH = 40;


window.onload = function(){
  ctx1.fillStyle = "#fff"
  ctx1.font = "bold 10pt sans-serif"
  drawBoard(map1,ctx1);
}
const map1 = [
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
];

function drawBoard(mapnum, ctxnum) {
  ctxnum.beginPath();

  for (let y = 0; y < mapH; y++) {
    for (let x = 0; x < mapW; x++) {
      switch(mapnum[((y*mapW)+x)]){
        case 0: //path
          ctx1.fillStyle = "#FFF"
          break;
        case 1: // wall
          ctx1.fillStyle = "#0000FF"
          break
        case 2: // food
          ctx1.fillStyle = "#00FF00"
          break
        case 3: // player
          ctx1.fillStyle = "#FFFF00"
          break
        case 4:// enemy
          ctx1.fillStyle = "#FF0000"
        break
        default: // error
          ctx1.fillStyle = "#0000"
      }
      ctxnum.fillRect(x*tileW, y*tileH, tileW, tileH)
      ctxnum.strokeStyle = "#a1a1a1"
      ctxnum.strokeRect(x*tileW, y*tileH, tileW, tileH)
    }
  }
}
