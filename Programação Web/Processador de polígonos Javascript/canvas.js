var canvas = document.getElementById("canvas"),
    ctx = canvas.getContext('2d');

// Tamanho do canvas
canvas.width = 600;
canvas.height = 600;

/*
    mouse = { x: 0, y: 0 }; 
    mouse_opt = {
        status: "up",
        point_index: -1,
        line: false,
        initial_click: { x: 0, y: 0 }
    };*/

// Create an empty array to store the lines
var lines = [];
var pointRadius = 6;

// Variables to handle mouse events
var mouse = { x: 0, y: 0 },
    mouseInfo = {
        state: "NotClicked",
        PointX: -1,
        PointY: -1,
        line: false,
        initial_click: { x: 0, y: 0 }
    };

//------------------FUNCTIONS

// Function to create a line object
function createLine(startX, endX, startY, endY, pointRadius) 
{
  return { startX, endX, startY, endY, pointRadius };
}

// Generate polygon based on the number of sides written by the user
function criaPoligono() 
{
    let size = 240,
    Xcenter = canvas.width/2,
    Ycenter = canvas.height/2,
    sides = document.getElementById("sides-number");
    numberOfSides = sides.value;
    let i;

    // Zera a quantidade de linhas
    lines = [];

    if (numberOfSides >= 3 && numberOfSides <= 8)
    {
        // Cria a primeira linha para os poligonos
        lines.push(createLine(
            Xcenter +  size * Math.cos(0),
            Xcenter + size * Math.cos(1 * 2 * Math.PI / numberOfSides),
            Ycenter +  size *  Math.sin(0),
            Ycenter + size * Math.sin(1 * 2 * Math.PI / numberOfSides),
            pointRadius
            ));

        for (i = 2; i <= numberOfSides; i++)
        {        
            lines.push(createLine(
                Xcenter + size * Math.cos((i - 1) * 2 * Math.PI / numberOfSides),
                Xcenter + size * Math.cos(i * 2 * Math.PI / numberOfSides),
                Ycenter + size * Math.sin((i - 1) * 2 * Math.PI / numberOfSides),
                Ycenter + size * Math.sin(i * 2 * Math.PI / numberOfSides),
                pointRadius
                ));
            }

        draw();
    }
    else
        alert("Impossível gerar um polígono com essa quantidade de lados!");
}

function draw ()
{
    let i;
    let line;
    let color = "purple";
    let pointWidth = 4;
    let pointBorderColor = "black";

    // Clear screen
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    // Draw lines
    for (i = 0; i < lines.length; i++)
    {
        line = lines[i]; 

        // Draw the line first
        ctx.beginPath();
            ctx.moveTo(line.startX, line.startY);
            ctx.lineTo(line.endX, line.endY);
            ctx.lineWidth = 6;
            ctx.stroke();
        ctx.closePath();      
        
        // Now the circles

        // Beginning
        ctx.beginPath();
            ctx.moveTo(line.startX, line.startY);
            ctx.arc(line.startX, line.startY, line.pointRadius, 0, 2 * Math.PI);
            ctx.fillStyle = color;
            ctx.lineWidth = pointWidth;
            ctx.strokeStyle = pointBorderColor;
            ctx.stroke();
            ctx.fill();
        ctx.closePath();

        // End
        ctx.beginPath();
            ctx.moveTo(line.endX, line.endY);
            ctx.arc(line.endX, line.endY, line.pointRadius, 0, 2 * Math.PI);
            ctx.fillStyle = color;
            ctx.lineWidth = pointWidth;
            ctx.strokeStyle = pointBorderColor;
            ctx.stroke();
            ctx.fill();
        ctx.closePath();
    }
}

// Event that checks if mouse was clicked on a line or a point
/*
function handleMouseDown(e)
{
    if (e.button != 2) 
    {
        mouse.x = e.clientX + window.scrollX;
        mouse.y = e.clientY + window.scrollY;
        mouse_opt.status = "down";
    
        // Save index of the clicked point
        for (var i = 0; i < points.length; i++) 
        {
            if ((mouse.x <= points[i].x + points[i].radius + 6) && (mouse.x >= points[i].x - points[i].radius - 6)
                && (mouse.y >= points[i].y - points[i].radius - 6) && (mouse.y <= points[i].y + points[i].radius + 6)) 
            {
                mouse_opt.point_index = i;
                break;
            }
        }  
        
        // Save coordenates if an line is clicked
        for (let value = 0; value <= 8; value++) 
        {
            if((ctx.isPointInStroke(mouse.x+value, mouse.y+value) || ctx.isPointInPath(mouse.x+value, mouse.y+value)) && mouse_opt.point_index == -1) 
            {
                mouse_opt.line = true;
                mouse_opt.initial_click.x = mouse.x;
                mouse_opt.initial_click.y = mouse.y;
                break;
            }
        }
    }
}*/

// ------------------EVENTS
/*
canvas.addEventListener("mousedown", handleMouseDown);
canvas.addEventListener('mouseup', handleMouseUp);
canvas.addEventListener('mousemove', handleMouseMove);
*/


// Add the first line to be drawn
lines.push(createLine(canvas.width/2 - 200, canvas.width/2 + 200, canvas.height/2, canvas.height/2, pointRadius));

// Main code
draw();

























/*

ctx.globalCompositeOperation = "lighter";




var points = [],
    n_points = 2,
    mouse = {
      x: 0,
      y: 0
    }; 
    mouse_opt = {
        status: "up",
        point_index: -1,
        line: false,
        initial_click: {
            x: 0, 
            y: 0
        }
    }


/*
    
// Draw the scene
function draw() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    // Clear lines
    for (let index = 0; index < points.length; index++) {
        points[index].connected = []
    }

    // Draw points
    for (let index = 0; index < points.length; index++) {
        let point = points[index];
        ctx.fillStyle = "black";
        ctx.beginPath();
        ctx.arc(point.x, point.y, point.radius, 0, 2 * Math.PI);
        ctx.fill();
        ctx.fillStyle = "black";
        ctx.stroke();
    }

    // Draw lines
    for (let index = 0; index < points.length-1; index++) {
        let point = points[index];
        let spoint = points[index+1];
        if (point.connected.length < 2) {
            point.connected.push({"vertex": spoint, "index": index+1, "equation": []});
            spoint.connected.push({"vertex": point, "index": index, "equation": []});
            ctx.moveTo(point.x, point.y);
            ctx.lineTo(spoint.x, spoint.y);
        }
    }

    // Drawa line between last and first point
    let point = points[0];
    if (point.connected.length < 2) {
        let spoint = points[points.length-1];
        ctx.moveTo(point.x, point.y);
        ctx.lineTo(spoint.x, spoint.y);
        point.connected.push({"vertex": spoint, "index": points.length-1, "equation": []});
        spoint.connected.push({"vertex":point, "index": 0, "equation": []});
    }

    // Define lines equations
    for (let index = 0; index < points.length; index++) {
        let point = points[index];
        for (let jndex = 0; jndex < point.connected.length; jndex++) {
            let a = (point.y - point.connected[jndex].vertex.y)/(point.x - point.connected[jndex].vertex.x);
            let b = (a * (-point.x)) + point.y;
            point.connected[jndex].equation = [a, b];
        }
    }

    ctx.lineWidth = 5;
    ctx.strokeStyle = "black";
    ctx.stroke();
}

// Adds point between two points of a click line
function addPoint(mouse) {
    for (let index = 0; index < points.length; index++) {
        let point = points[index];
        for (let jndex = 0; jndex < point.connected.length; jndex++) {
            let y = (point.connected[jndex].equation[0]*mouse.x)+point.connected[jndex].equation[1];
            if (Math.abs(y - mouse.y) <= 10) {
                if ((index == 0) && (point.connected[jndex].index == points.length - 1)) {
                    points.push({x: mouse.x, y: mouse.y, radius: 4, connected: []});
                    return draw();
                } else {
                    points.splice(index+1, 0, {x: mouse.x, y: mouse.y, radius: 4, connected: []});
                    return draw();
                }
            }
        } 
    }
}


*/


























/*
// Event for clicking on points or lines
canvas.addEventListener('mousedown', function(e) {
    if (e.button != 2) {
        mouse.x = e.clientX + window.scrollX;
        mouse.y = e.clientY + window.scrollY;
        mouse_opt.status = "down";
    
        // Save index of the clicked point
        for (var i = 0; i < points.length; i++) {
            if ((mouse.x <= points[i].x + points[i].radius + 6) && (mouse.x >= points[i].x - points[i].radius - 6)
                && (mouse.y >= points[i].y - points[i].radius - 6) && (mouse.y <= points[i].y + points[i].radius + 6)) {
                    mouse_opt.point_index = i;
                    break;
            }
        }  
        
        // Save coordenates if an line is clicked
        for (let value = 0; value <= 8; value++) {
            if((ctx.isPointInStroke(mouse.x+value, mouse.y+value) || ctx.isPointInPath(mouse.x+value, mouse.y+value)) && mouse_opt.point_index == -1) {
                mouse_opt.line = true;
                mouse_opt.initial_click.x = mouse.x;
                mouse_opt.initial_click.y = mouse.y;
                break;
            }
        }
    }
});

// Event for clearing the click infos
canvas.addEventListener('mouseup', function(e) {
    mouse_opt.status = "up";
    mouse_opt.point_index = -1;
    mouse_opt.line = false;
});

// Event for handling mouse movement of points or lines
canvas.addEventListener('mousemove', function(e) {
    mouse.x = e.clientX + window.scrollX;
    mouse.y = e.clientY + window.scrollY;

    if (mouse_opt.line) {
        for (var i = 0; i < points.length; i++) {
            let newpx = points[i].x + mouse.x - mouse_opt.initial_click.x;
            let newpy = points[i].y + mouse.y - mouse_opt.initial_click.y;
            if (newpx >= canvas.width || newpx <= 0) {
                return;
            } else if (newpy >= canvas.height || newpy <= 0) {
                return;
            }
        }
        for (var i = 0; i < points.length; i++) {
            points[i].x += mouse.x - mouse_opt.initial_click.x;
            points[i].y += mouse.y - mouse_opt.initial_click.y;
        }
        mouse_opt.initial_click.x = mouse.x;
        mouse_opt.initial_click.y = mouse.y;
        draw();
    } else if (mouse_opt.status == "down" && mouse_opt.point_index != -1) {
        points[mouse_opt.point_index].x = mouse.x;
        points[mouse_opt.point_index].y = mouse.y;
        draw();
    }
});

// Event for right click lines
canvas.addEventListener('contextmenu', function(e) {
    mouse.x = e.clientX + window.scrollX;
    mouse.y = e.clientY + window.scrollY;
    
    for (let value = 0; value <= 8; value++) {
        if((ctx.isPointInStroke(mouse.x+value, mouse.y+value) || ctx.isPointInPath(mouse.x+value, mouse.y+value)) && mouse_opt.point_index == -1) {
            e.preventDefault();
            addPoint(mouse);
            break;
        }
    }
    return false;
}, false);


hide.addEventListener('click', function(e) {
    let form = document.getElementById("form");
    if (form.classList.contains("hidden")) {
        form.classList.remove('hidden');
        hide.firstChild.data = "Esconder";
    } else {
        form.classList.add('hidden');
        hide.firstChild.data = "Mostrar";
    }
})

hide_help.addEventListener('click', function(e) {
    let form = document.getElementById("help");
    if (form.classList.contains("hidden")) {
        form.classList.remove('hidden');
    } else {
        form.classList.add('hidden');
    }
})

*/