class A:
    def getA(self):
        return 'a'

    def getWrongA(self):
        return 'b'

if __name__ == '__main__':
    aa = A() 
    print aa.getA()
