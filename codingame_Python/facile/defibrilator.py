import sys # To debug: print("Debug messages...", file=sys.stderr)
import math

class Defibrillator:
    def __init__(self, name, lon, lat):
        self.name = name;
        self.lon = lon;
        self.lat = lat;
    def distanceTo(self, lon, lat):
        x = (self.lon - lon) * math.cos(0.5 * (lat + self.lat));
        y = lat - self.lat;
        return math.sqrt(x * x + y * y) * 6371;

lon = (math.pi / 180) * float(input().replace(',', '.'))
lat = (math.pi / 180) * float(input().replace(',', '.'))
n = int(input())

defibs = []
for i in range(n):
    d = input().split(';')
    defibs.append(Defibrillator(d[1],
        (math.pi / 180) * float(d[4].replace(',', '.')),
        (math.pi / 180) * float(d[5].replace(',', '.'))));

defibs.sort(key=lambda d: d.distanceTo(lon, lat))
print(defibs[0].name)