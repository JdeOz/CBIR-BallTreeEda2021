const descargar = document.querySelector("#descargar");
let myCanvas = document.querySelector('#pizarra');

descargar.addEventListener("click", function (event) {
    let dataURL = myCanvas.toDataURL("image/jpeg");
    let k = document.getElementById('k').value;
    console.log(dataURL)
    console.log(k)
    $.ajax({
        type: "POST",
        url: "/hook",
        data: {
            imageBase64: dataURL,
            ks: k
        }
    }).done(function () {
        console.log('sent');
    });
    event.preventDefault();
    setTimeout(() => location.href = "/", 500);
});

