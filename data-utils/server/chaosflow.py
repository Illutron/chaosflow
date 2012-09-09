from bson.objectid import ObjectId
from flask import Flask, render_template

from bson.json_util import dumps
import pymongo

# configuration
DEBUG = True 

app = Flask(__name__)
app.config.from_object(__name__)

connection = pymongo.Connection("localhost", 27017)
db = connection.chaosflow

stat_buckets = db.stat_buckets
stat_entries = db.stat_entries


@app.route("/")
def index():
    return render_template('index.html')

@app.route("/locations")
def locations():
    return dumps(stat_buckets.find())

@app.route("/locations/<location_id>")
def location(location_id):
    return dumps(stat_buckets.find_one({"_id": ObjectId(location_id)}))

@app.route("/locations/<location_id>/entries")
def entries_for_location(location_id):
    return dumps(stat_entries.find({"stat_bucket": ObjectId(location_id)}))

if __name__ == "__main__":
    app.run()