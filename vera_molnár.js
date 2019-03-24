MARGIN_X=30;
MARGIN_Y=30;

function setup() {
  createCanvas(800, 800);
}

function bars(row_idx,col_idx, orientation, count){
	col = (col_idx * 87);
	row = (row_idx * 87);

	limit=count*2;
	cube_x = 80;
	cube_y = 80/limit;

	JOIN = 6;
	LEFT_POS  = col+MARGIN_X;
	TOP       = row+MARGIN_Y;
	RIGHT_POS = LEFT_POS+cube_x;
	BOTTOM    = TOP+cube_x;

	if(orientation == 'top'){
		for(var i=0;i<limit; i++){
      	line(LEFT_POS+cube_y*i, TOP, LEFT_POS + cube_y*i, BOTTOM);
			if((i%2)==0){
				line(LEFT_POS+cube_y*(i+1),  BOTTOM, LEFT_POS + cube_y*i, BOTTOM);
			}
			else{
		 		line(LEFT_POS+cube_y*(i+1), TOP, LEFT_POS + cube_y*i, TOP);
			}
		}

		line(LEFT_POS+cube_y*limit,     TOP, LEFT_POS + cube_y*limit, BOTTOM);
		if(col_idx != 4){
			line(LEFT_POS+cube_y*(limit+1), BOTTOM, LEFT_POS + cube_y*limit, BOTTOM);
		}
		else{
			line(LEFT_POS+cube_y*(limit), BOTTOM, LEFT_POS + cube_y*limit, BOTTOM+ JOIN);
		}
	}
	else{//side
		for(var i=0;i<limit;i++){
      line(LEFT_POS, TOP+cube_y*i, LEFT_POS+cube_x, TOP+cube_y*i);
			if((i%2) == 0){
				line(LEFT_POS, 		    TOP+cube_y*i, LEFT_POS,        TOP+cube_y*(i+1));
			}else{
 				line(LEFT_POS+cube_x, TOP+cube_y*i, LEFT_POS+cube_x, TOP+cube_y*(i+1));
			}
		}
		line(LEFT_POS, TOP+cube_y*limit,  LEFT_POS+cube_x, TOP+cube_y*limit);

		if(col_idx != 4 && col_idx != 0){
			line(LEFT_POS+cube_x, TOP,  LEFT_POS+cube_x + JOIN, TOP);
		}
		if(col_idx === 0){
			line(LEFT_POS+cube_x, TOP,  LEFT_POS+cube_x+JOIN, TOP);
			line(LEFT_POS, TOP+cube_y*limit, LEFT_POS, TOP+cube_y*(limit+1));
		}
	}
}

function side_bars(row_idx, col_idx, count){
	bars(row_idx, col_idx, 'side', count)
}

function top_bars(row_idx, col_idx, count){
	bars(row_idx, col_idx, 'top', count)
}

BAR_TOP = function(count){
  fn=function(row_idx, col_idx){
		bars(row_idx, col_idx, 'top', count)
  }
  return fn
}

BAR_SIDE = function(count){
  fn =function(row_idx, col_idx){
		bars(row_idx, col_idx, 'side', count)
  }
  return fn
}

function draw() {
  background(235);
	strokeWeight(2.2)

	grid=[
    [BAR_TOP(2),  BAR_SIDE(6), BAR_TOP(4),  BAR_SIDE(6), BAR_TOP(4)],
    [BAR_SIDE(2), BAR_TOP(6),  BAR_SIDE(6), BAR_TOP(4),  BAR_SIDE(6)],
    [BAR_TOP(4),  BAR_SIDE(4), BAR_TOP(2),  BAR_SIDE(6), BAR_TOP(4)],
    [BAR_SIDE(2), BAR_TOP(2),  BAR_SIDE(6), BAR_TOP(3),  BAR_SIDE(2)],
    [BAR_TOP(2),  BAR_SIDE(6), BAR_TOP(3),  BAR_SIDE(3), BAR_TOP(2)],
  ]

  for(var row=0;row<grid.length;row++){
	  for(var col=0;col<grid[row].length;col++){
      fn = grid[row][col];
  		fn(row,col);
    }
  }
	stroke(90);
}
