var canvas = document.getElementById("canvas"),
    ctx = canvas.getContext('2d'),
    canvasRect = canvas.getBoundingClientRect();

// Canvas size
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
var points = [];
var lineWidth = 6;
var pointRadius = 6;

// Variables to handle mouse events
var mouse = { x: 0, y: 0 },
    mouseInfo = {
        state: "NotClicked",
        pointIndex: -1,
        lineIndex: -1,
        line: false,
        initial_click: { x: 0, y: 0 }
    };
//------------------FUNCTIONS
function createPoint(x, y)
{
    return { x, y };
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

    // Set the points array to zero
    points = [];

    if (numberOfSides >= 3 && numberOfSides <= 8)
    {
        points.push(createPoint(Xcenter + size * Math.cos(0), Ycenter + size *  Math.sin(0)));

        for (i = 1; i <= numberOfSides - 1; i++)
        {        
            points.push(createPoint(Xcenter + size * Math.cos(i * 2 * Math.PI / numberOfSides),
                Ycenter + size * Math.sin(i * 2 * Math.PI / numberOfSides),
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
    let pointRadius = 6;
    
    // Clear screen
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    ctx.beginPath();
        ctx.moveTo(points[0].x, points[0].y);
        ctx.lineWidth = lineWidth;
    
    // Draw lines
    for (i = 1; i < points.length; i++)
    {
        p = points[i]; 
        ctx.lineTo(p.x, p.y);
    }
        ctx.stroke();
    ctx.closePath();

    // Connecting the first point to the last point
    // cause we didn't do that in the previous loop
    ctx.beginPath();
        ctx.moveTo(points[0].x, points[0].y);
        ctx.lineWidth = lineWidth;
        ctx.lineTo(points[points.length - 1].x, points[points.length - 1].y);
        ctx.stroke();
    ctx.closePath();

    // Draw points
    for (i = 0; i < points.length; i++)
    {
        ctx.beginPath();
            ctx.moveTo(points[i].x, points[i].y);
            ctx.arc(points[i].x, points[i].y, pointRadius, 0, 2 * Math.PI);
            ctx.fillStyle = color;
            ctx.lineWidth = pointWidth;
            ctx.strokeStyle = pointBorderColor;
            ctx.stroke();
            ctx.fill();
        ctx.closePath();
    }
}

function handleMouseDown(e) 
{
    let i;
    let startPoint, endPoint;

    // Left click
    if (e.button !== 2) 
    {
        mouse.x = e.clientX - canvasRect.left;
        mouse.y = e.clientY - canvasRect.top;
        mouseInfo.state = "Clicked";

        endPoint = points[0];

        if (isMouseOnPoint(mouse.x, mouse.y, endPoint.x, endPoint.y)) 
        {
            // Store the index of the point
            mouseInfo.pointIndex = 0;
            //console.log(mouseInfo.pointIndex);
            return;
        }
  
        // Check if clicked on a point
        for (i = 0; i < points.length - 1; i++) 
        {
            startPoint = points[i];
            endPoint = points[i + 1];

            if (isMouseOnPoint(mouse.x, mouse.y, endPoint.x, endPoint.y)) 
            {
                // Store the index of the point
                mouseInfo.pointIndex = i + 1;
                //console.log(mouseInfo.pointIndex);
                break;
            }

            else if (isMouseOnLine(mouse.x, mouse.y, startPoint.x, startPoint.y, endPoint.x, endPoint.y, lineWidth))
            {
                // Store the index of the line
                mouseInfo.lineIndex = i;
                //console.log(i);
                break;
            }
            
        }

        // Treating the last line of the polygon
        if (isMouseOnLine(mouse.x, mouse.y, points[0].x, points[0].y, points[points.length - 1].x, points[points.length - 1].y, lineWidth))
        {
            // Store the index of the line
            mouseInfo.lineIndex = points.length - 1;
           //console.log(points.length);
        }
    }

    // Right click
    else
    {
        mouse.x = e.clientX - canvasRect.left;
        mouse.y = e.clientY - canvasRect.top;
        mouseInfo.state = "Clicked";

        endPoint = points[0];

        // Check if clicked on a point
        for (i = 0; i < points.length - 1; i++) 
        {
            startPoint = points[i];
            endPoint = points[i + 1];
        
            if (isMouseOnLine(mouse.x, mouse.y, startPoint.x, startPoint.y, endPoint.x, endPoint.y, lineWidth))
            {
                addPoint(points, mouse.x, mouse.y, i);
                //console.log(i);
                break;
            }
        }

        // Treating the last line of the polygon
        if (isMouseOnLine(mouse.x, mouse.y, points[0].x, points[0].y, points[points.length - 1].x, points[points.length - 1].y, lineWidth))
        {
            addPoint(points, mouse.x, mouse.y, points.length - 1);
            //console.log(i);
        }
    }
}

function addPoint(points, x, y, index) 
{
    const newPoint = { x, y };

    points.splice(index + 1, 0, newPoint);
}

function isMouseOnLine(x, y, startX, startY, endX, endY, lineWidth)
{  
    let dx, dy, lineLength, distance;
    
  // Calculate the distance between the point and the line
    dx = endX - startX;
    dy = endY - startY;
    lineLength = Math.sqrt(dx * dx + dy * dy);

    distance = Math.abs(dy * x - dx * y + endX * startY - endY * startX) / lineLength;

    // Check if the distance is within the threshold (considering line width)
    // Adding 2 to the lineWidth for tolerance
    return distance <= (lineWidth + 2) / 2;
}

function isMouseOnPoint(x, y, pointX, pointY) 
{
    let distance;

    // Distance between two poins formula
    distance = Math.sqrt((x - pointX) ** 2 + (y - pointY) ** 2);
    
    // Addint 4 to the pointRadius for tolerance
    return distance <= pointRadius + 4;
}

function handleMouseMove(e)
{
    let point;
    let dx, dy;

    // If the user clicked on a point
    if (mouseInfo.state === "Clicked" && mouseInfo.pointIndex !== -1) 
    {
        point = points[mouseInfo.pointIndex];

        point.x = e.clientX - canvasRect.left;
        point.y = e.clientY - canvasRect.top;
        draw();
    }

    // If clicked on a line
    else if (mouseInfo.state === "Clicked" && mouseInfo.lineIndex !== -1)
    {
        if (mouseInfo.lineIndex === points.length - 1)
        {        
            startPoint = points[mouseInfo.lineIndex];
            endPoint = points[0];
        }
        else
        {
            startPoint = points[mouseInfo.lineIndex];
            endPoint = points[mouseInfo.lineIndex + 1];
        }
    
        // Gets the difference between last position and the position it should
        // have when the user moves the line
        dx = e.clientX - canvasRect.left - (startPoint.x + endPoint.x) / 2;
        dy = e.clientY - canvasRect.top - (startPoint.y + endPoint.y) / 2;
    
        startPoint.x += dx;
        startPoint.y += dy;
    
        endPoint.x += dx;
        endPoint.y += dy;
    
        draw();
    } 
}
    
function handleMouseUp(e) 
{
    mouseInfo.state = "NotClicked";
    mouseInfo.pointIndex = -1;
    mouseInfo.lineIndex = -1;
} 

// ------------------EVENTS

canvas.addEventListener("mousedown", handleMouseDown);
canvas.addEventListener("mousemove", handleMouseMove);
canvas.addEventListener("mouseup", handleMouseUp);

// Main code

// Add first point
points.push(createPoint(canvas.width/2 + 240 * Math.cos(0), canvas.width/2 + 240 *  Math.sin(0)));
points.push(createPoint(canvas.width/2 + 240 * Math.cos(1 * 2 * Math.PI / 2), canvas.width/2 + 240 * Math.sin(1 * 2 * Math.PI / 2),
                ));

draw();