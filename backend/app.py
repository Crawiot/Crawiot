from flask import Flask, render_template, Response

app = Flask(__name__)


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/api/target', methods=['POST'])
def target():
    return render_template('index.html', success=True)


@app.route('/api/traces')
def traces():
    return Response('traces', mimetype='text/plain')


if __name__ == '__main__':
    app.run()
