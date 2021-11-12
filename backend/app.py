from flask import Flask, render_template, Response, request

from strategic import handle_post_target
import car_api

app = Flask(__name__)


@app.route('/')
def index():
    return index_page(None)


@app.route('/api/target', methods=['POST'])
def target():
    try:
        x = int(request.form.get('X'))
        y = int(request.form.get('Y'))
    except (TypeError, ValueError):
        return Response("Invalid body", status=400)

    success = handle_post_target(x, y)
    return index_page(success=success)


def index_page(success):
    current_location = car_api.get_location()
    return render_template('index.html', success=success, current_location=current_location)


@app.route('/api/traces')
def traces():
    traces_text = car_api.get_traces()
    return Response(traces_text, mimetype='text/plain')


if __name__ == '__main__':
    app.run()
