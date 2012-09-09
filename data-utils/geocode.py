# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from pymongo import Connection
from geopy import geocoders
import time

connection = Connection('127.0.0.1', 27017)
db = connection.chaosflow
stat_buckets = db.stat_buckets

g = geocoders.Google(domain="maps.google.dk")

def split(txt, seps):
    default_sep = seps[0]
    for sep in seps[1:]: # we skip seps[0] because that's the default seperator
        txt = txt.replace(sep, default_sep)
    return [i.strip() for i in txt.split(default_sep)]


for bucket in stat_buckets.find():
    time.sleep(1) # As to not hit googles request limit

    if not bucket.get('lat') and not bucket.get('lng'):
        while True:
            attempt_count = 0
            try:
                attempt_count += 1

                splits = ["ø.f.", "n.f.", "v.f.", "nø.f.", "sv.f.", "s.f.", "sydøst for", "syd for", "øst for", "nv. for"]
                location_name = "{}, København".format(split(bucket['road'], splits)[0])

                print "Attempt {} at looking up geocoordinates for {}.".format(attempt_count, location_name)
                place, (lat, lng) = g.geocode(location_name.encode('UTF-8'))
                
            except geocoders.google.GQueryError as e:
                print "ERROR: {}".format(e)
                break
            except ValueError as e:
                print "ERROR: {}".format(e)
                break
            except geocoders.google.GTooManyQueriesError as e:
                if attempt_count < 4:
                    print "To many requests. Will retry in 10 seconds."
                    print "ERROR: {}".format(e)
                    time.sleep(10)
                    continue
                else:
                    print "To many requests. Will not retry."
                    break
            else:
                print u"SUCCESS: Geocoordinates found for {}: {}, {}".format(place, lat, lng)
                stat_buckets.update({"_id": bucket["_id"] },
                    { "$set": {"lat": lat, "lng": lng}})

                break

