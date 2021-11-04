from flask import Flask, render_template, Response, request
from car_api import get_traces, post_target
from strategic import handle_post_target

app = Flask(__name__)


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/api/target', methods=['POST'])
def target():
    try:
        x = int(request.form.get('X'))
        y = int(request.form.get('Y'))
    except (TypeError, ValueError):
        return Response("Invalid body", status=400)

    success = handle_post_target(x, y)
    return render_template('index.html', success=success)


@app.route('/api/traces')
def traces():
    traces_text = get_traces()
    return Response(traces_text, mimetype='text/plain')


if __name__ == '__main__':
    app.run()
