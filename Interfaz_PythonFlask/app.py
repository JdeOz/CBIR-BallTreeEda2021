from functions import *
from flask import Flask, render_template, request, flash, redirect, url_for
import base64
import io
import subprocess
from PIL import Image, ImageOps
import numpy as np

app = Flask(__name__)
app.config["UPLOAD_FOLDER"] = "static/up/"
k = 18


# Página principal
# noinspection PyTypeChecker
@app.route('/')
def namePage():
    img = Image.open('static/up/up.bmp')
    gray_image = ImageOps.grayscale(img)
    gray = np.array(gray_image)
    bitMap = str(k) + ";"
    for i in gray:
        for j in i:
            bitMap += str(j) + ","
    fifoWrite(bitMap)
    ans = fifoRead()
    vectorAns = ans.split(",")
    res = []
    for i in reversed(vectorAns):
        res.append(int(i))
    return render_template('index.html', images=res, k=k)


# Ruta para subir la imagen como archivo
@app.route('/uploader', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        global k
        k = int(request.form['k2'])

        if 'file' not in request.files:
            flash('No file part')
            return redirect(request.url)  # No funciona
        f = request.files['file']
        if f.filename == '':
            flash('No selected file')
            return redirect(request.url)  # No funciona

        if f and allowed_file(f.filename):
            f.save(app.config['UPLOAD_FOLDER'] + "up.bmp")
            return redirect(url_for('namePage'))


# Ruta para recibir el dibujo de la pizarra
@app.route('/hook', methods=['POST'])
def get_image():
    global k
    k = int(request.values['ks'])
    image_b64 = request.values['imageBase64']
    lectura = base64.decodebytes(image_b64.split(',')[1].encode())
    stream = io.BytesIO(lectura)
    img = Image.open(stream)
    fix_size = img.resize((28, 28))
    gray = ImageOps.grayscale(fix_size)
    gray.save("static/up/up.bmp")
    return "listo"


# Inicio mi comunicación IPC con C++
makeFifo()
print("Indexando...")
p = subprocess.Popen("./BallTreeInterface")
pid = int(fifoRead())
if pid:
    print("Programa iniciado")

# Inicio flask
if __name__ == '__main__':
    app.run()
