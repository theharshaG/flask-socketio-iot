from flask import Flask, render_template, request, jsonify
from flask_sqlalchemy import SQLAlchemy
from flask_socketio import SocketIO

app = Flask(__name__)

# DB config
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///iot.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

db = SQLAlchemy(app)
socketio = SocketIO(app)

# Model
class Sensor(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    motion = db.Column(db.Integer)

with app.app_context():
    db.create_all()

# -------------------------------
# RECEIVE DATA FROM ESP32
# -------------------------------
@app.route('/add', methods=['POST'])
def add_data():
    data = request.get_json()
    motion = data.get('motion')

    new_data = Sensor(motion=motion)
    db.session.add(new_data)
    db.session.commit()

    # 🔥 SEND REAL-TIME UPDATE
    socketio.emit('new_data', {"motion": motion})

    return jsonify({"message": "Saved"})

# -------------------------------
# DASHBOARD
# -------------------------------
@app.route('/')
def home():
    return render_template('index.html')

# -------------------------------
# RUN
# -------------------------------
if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5001, debug=True)
