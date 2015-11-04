def ask_ok( prompt, retries = 4, complaint = 'Yes or no, please!' ):
    while True:
        ok = input( prompt )

        if ok in ( 'y', 'ye', 'yes' ):
            return True
        elif ok in ( 'n', 'no', 'nop', 'nope' ):
            return False
        
        retries = retries - 1

        if retries <= 0:
            raise OSError('uncooperative user')
        print( complaint )

print( ask_ok('Do you really wanna Quit?') )
