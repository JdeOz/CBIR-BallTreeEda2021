import os

# Variables globales para las funciones
ALLOWED_EXTENSIONS = {'bmp', 'png', 'jpg', 'jpeg'}
CP = "/tmp/CP"  # Read
PC = "/tmp/PC"  # Write
MAX_BUF = 3137

# Función que reconoce si el archivo enviado es correcto
def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS


def fifoWrite(n):
    fd = os.open(PC, os.O_WRONLY)
    n += "\0"
    n_bytes = bytes(n, 'UTF-8')
    os.write(fd, n_bytes)
    os.close(fd)


def fifoRead():
    fd = os.open(CP, os.O_RDONLY)
    data = os.read(fd, MAX_BUF)
    os.close(fd)
    x = data.decode('UTF-8')
    return x


def makeFifo():
    try:
        os.mkfifo(CP)
    except:
        pass
    try:
        os.mkfifo(PC)
    except:
        pass
