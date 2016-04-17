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
//let myTextView = myScrollView as! UITextView //downCasting
// downCasting을 force로 하는 것보다 가능한지 체크하는 로직이 있으면 좋음... 이건 책에서 나중에 필요할 때 보자!

//: ## Collection Types

//: ### Array
//: * create Empty Array
var intList = [Int]()
print("intList에는 \(intList.count)만큼이 있다.")

//: * append
intList.append(3)
intList.append(4)
intList.count
intList = []
intList.count

//: * create array with Default value
var threeDoubles = [Double](count:3, repeatedValue: 0.0)
var anotherThreeDoubles = [Double](count: 3, repeatedValue: 2.5)
var sixDoubles = threeDoubles + anotherThreeDoubles

var shoppingList : [String] = ["Eggs", "Milk"]
if shoppingList.isEmpty {
    print("The shopping list is empty.")
} else {
    print("The shopping list is not empty.")
}
shoppingList += ["Baking Powder"]
shoppingList += ["Chocolate Spread", "Cheese", "Butter"]
var firstItem = shoppingList[0] // value copy
shoppingList[0] = "Six eggs"
shoppingList[4...5] = ["Bananas", "Apples"]


//: ### Set
/*: 배열과 다르다.
 * 순서 보장 X
 * 같은 값이 중복 X
 * 넣을 데이터는 Hashable protocol이 존재해야함
 */

//: * 초기화 방법
//빈 초기화
var genres1 : Set<String> = [ ]
var genres2 = Set<String>()
// 값이 있는 초기화
var genres3 : Set = ["Classic", "Rock", "Balad"]
var genres4 : Set<String> = ["Classic", "Rock", "Balad"]

//: * insert
genres1.insert("Classic")
genres1.insert("Rock")
genres1.insert("Balad")

genres1.insert("Classic") // 한번 더 넣어도 무시가 됨
//: * isEmpty
if genres1.isEmpty{
    print("Set is empty")
} else{
    print("Set has \(genres1.count) data")
}
//: * sort + for in
var strList : [String] = []
for g in genres1.sort(){
    strList.append(g)
}
strList

//: * remove
//: 삭제할 것을 찾으면 return하고 없으면 nil return!
if let removedItem = genres1.remove("Rock"){
    print("\(removedItem) was removed.")
} else{
    print("There is no removedItem")
}
if let removedItem = genres1.remove("Rock"){
    print("\(removedItem) was removed.")
} else{
    print("There is no removedItem")
}
//: * removeAll
genres1.removeAll()

if genres1.isEmpty{
    print("Set is empty")
} else{
    print("\(genres1.count) data exist.")
}
//: * contains
if genres1.contains("Rock"){
    print("Rock exists in the Set")
} else{
    print("Rock doesn't exist in the Set")
}

//: ### 집합연산
let oddDigits : Set = [ 1, 3, 5, 7, 9 ]
let evenDigits : Set = [2, 4, 6, 8]
let primeDigits : Set = [2, 3, 5, 7]

oddDigits.intersect(evenDigits).sort()

oddDigits.exclusiveOr(primeDigits).sort()

oddDigits.union(evenDigits).sort()

oddDigits.subtract(primDigits).sort()


//: [Next](@next)
