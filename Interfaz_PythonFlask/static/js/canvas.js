// Pizarra, extraído del siguiente enlace https://programadorwebvalencia.com/dibujar-con-el-raton-en-HTML-y-Javascript/
//======================================================================
// VARIABLES
//======================================================================
let miCanvas = document.querySelector('#pizarra');
let lineas = [];
let correccionX = 0;
let correccionY = 0;
let pintarLinea = false;
// Marca el nuevo punto
let nuevaPosicionX = 0;
let nuevaPosicionY = 0;

let posicion = miCanvas.getBoundingClientRect()
correccionX = posicion.x;
correccionY = posicion.y;

miCanvas.width = 200;
miCanvas.height = 200;

//Descargar


//======================================================================
// FUNCIONES
//======================================================================

/**
 * Función que empieza a dibujar la linea
 */
function empezarDibujo() {
    pintarLinea = true;
    lineas.push([]);
}

/**
 * Función que guarda la posición de la nueva línea
 */
function guardarLinea() {
    lineas[lineas.length - 1].push({
        x: nuevaPosicionX,
        y: nuevaPosicionY
    });

}

/**
 * Función dibuja la linea
 */
function dibujarLinea(event) {
    event.layerY = undefined;
    event.layerX = undefined;
    event.preventDefault();
    if (pintarLinea) {
        let ctx = miCanvas.getContext('2d')
        // Estilos de linea
        ctx.lineJoin = ctx.lineCap = 'round';
        ctx.lineWidth = 14;
        // Color de la linea
        ctx.strokeStyle = '#fff';
        // Marca el nuevo punto
        if (event.changedTouches === undefined) {
            // Versión ratón
            nuevaPosicionX = event.layerX;
            nuevaPosicionY = event.layerY;
        } else {
            // Versión touch, pantalla táctil
            nuevaPosicionX = event.changedTouches[0].pageX - correccionX;
            nuevaPosicionY = event.changedTouches[0].pageY - correccionY;
        }
        // Guarda la linea
        guardarLinea();
        // Redibuja todas las lineas guardadas
        ctx.beginPath();
        lineas.forEach(function (segmento) {
            ctx.moveTo(segmento[0].x, segmento[0].y);
            segmento.forEach(function (punto) {
                ctx.lineTo(punto.x, punto.y);
            });
        });
        ctx.stroke();
    }
}


/**
 * Función que deja de dibujar la linea
 */
function pararDibujar() {
    pintarLinea = false;
    guardarLinea();

}

//======================================================================
// EVENTOS
//======================================================================

// Eventos ratón
miCanvas.addEventListener('mousedown', empezarDibujo, false);
miCanvas.addEventListener('mousemove', dibujarLinea, false);
miCanvas.addEventListener('mouseup', pararDibujar, false);

// Eventos pantallas táctiles
miCanvas.addEventListener('touchstart', empezarDibujo, false);
miCanvas.addEventListener('touchmove', dibujarLinea, false);
