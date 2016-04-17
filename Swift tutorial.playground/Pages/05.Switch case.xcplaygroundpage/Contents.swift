//: [Previous](@previous)
/*:
 ## switch case문
 * 기본적인 switch case
 */
var x = 1

switch x
{
case 0:
    print( "0" )
case 1:
    print( "1" )
default:
    print( "default" )
}

/*:
 * combining switch case
 */
x = 2

switch x
{
case 0:
    print( "0" )
case 1,2:
    print( "1,2" )
default:
    print( "default" )
}

/*:
 * range switch case
 */
x = 2

switch x
{
case 0:
    print( "0" )
case 1...3:
    print( "1...3" )
default:
    print( "default" )
}
/*:
 * where 절이 들어간 switch case
 where절로 추가적인 조건을 줄 수 있음
 */
var temperature = 54

switch (temperature)
{
case 0...49 where temperature % 2 == 0:
    print("Cold and even")
case 50...79 where temperature % 2 == 0:
    print("Warm and even")
case 80...110 where temperature % 2 == 0:
    print("Hot and even")
    
default:
    print("Temperature out of range or odd")
}

/*:
 * fallthrough
 fallthrough를 사용하여 break를 안 쓴 효과를 내자!
 */
temperature = 10

switch (temperature)
{
case 0...49 where temperature % 2 == 0:
    print("Cold and even")
    fallthrough
case 50...79 where temperature % 2 == 0:
    print("Warm and even")
    fallthrough
case 80...110 where temperature % 2 == 0:
    print("Hot and even")
    fallthrough
default:
    print("Temperature out of range or odd")
}
//: [Next](@next)
