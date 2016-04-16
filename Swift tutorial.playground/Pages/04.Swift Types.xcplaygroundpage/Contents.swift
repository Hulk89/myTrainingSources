//: [Previous](@previous)

import Foundation
import UIKit
/*: 
 ## Swift Types
 swift type을 정리한다.
 */


/*:
 ### Integer
 * Signed   : Int8,  Int16,  Int32, Int64
 * Unsigned : UInt8, UInt16, UInt32, UInt64
 */

print("Int32 Min = \(Int32.min) \nInt32 Max = \(Int32.max)")
print("Int Min = \(Int.min) \nInt Max = \(Int.max)")

/*:
 ### Float & Double
 * float  : 유효숫자 6개
 * double : 유효숫자 15개

 ### Bool
 true false
 
 ### Character
 */
var myChar1 = "f"
var myChar2 = ":"
var myChar3 = "X"
// unicode는 다음처럼 세팅한다.
var myChar4 = "\u{0058}"

/*:
 ### String
 */
var userName = "John"
var inboxCount = 25
let maxCount = 100

var message = "\(userName) has \(inboxCount) message. Message capacity remaining is \(maxCount - inboxCount)"
print(message)

/*:
 ### Tuple
 */
let myTuple = (10, 432.433, "이것은 스트링이다.") // 각기 다른 type을 같이 넣을 수 있다.
let myString = myTuple.2 // index로 접근하혀면 이렇게 쓰면 된다.

var (myInt, myFloat, myString2) = myTuple // 이렇게 벗겨낼 수 있다.
myInt
myFloat
myString2
var (myInt3, _, myString3) = myTuple // _는 extraction에서 무시된다.

let myTupleByName = (count: 10, length: 432.433, message: "This is a String") // 이름으로 조회할 수 있게 만들자.
//다음 두 코드는 같은 일을 한다.
myTupleByName.count
myTupleByName.0

/*:
 ## Optional Type
 이건 나중에 정리하자 귀찮아...
 */



/*: 
 ## Type casting
 upcasting, downcasting
 */
let myButton: UIButton = UIButton()
let myControl = myButton as UIControl //upCasting

let myScrollView: UIScrollView = UIScrollView()
let myTextView = myScrollView as! UITextView //downCasting
// downCasting을 force로 하는 것보다 가능한지 체크하는 로직이 있으면 좋음... 이건 책에서 나중에 필요할 때 보자!

//: [Next](@next)
