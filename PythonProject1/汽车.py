class Car:
    def __init__(self,mode,make,year,milage):
        self.mode=mode
        self.make=make
        self.year=year
        self.milage=0
    def scriptive(self):
        scriptive=f"{self.mode}  {self.make}  {self.year}"
        print(scriptive)
