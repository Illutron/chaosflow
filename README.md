Abstract data visualization of Copenhagens bike traffic for an installation at the 4S/EASST conferences 2012. 

Get the raw data at http://ge.tt/3mnABAM/v/0

Install and run mongodb:
You can get mongo db using npm. Get node and npm from http://nodejs.org/download/.

    $ npm install mongodb
    $ mongod --dbpath data-utils/db 

Set up a python virtualenv and isntall requirements:
Get virtualenv and pip from http://www.pip-installer.org/.
    $ mkvirtualenv chaosflow
    $ pip install -r data-utils/requirements.txt

Import data from excel files to mongo db using the python import script. Do a geocode lookup on every entry:  
    
    $ python import.py
    $ python geocode.py

Run the server:

    $ python server/chaosflow.py

Then you can run the openframeworks app.