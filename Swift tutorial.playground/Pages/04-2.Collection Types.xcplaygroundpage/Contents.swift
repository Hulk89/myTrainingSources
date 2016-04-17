//: [Previous](@previous)

import UIKit

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
let image = UIImage(named: "Venn.png")
let oddDigits : Set = [ 1, 3, 5, 7, 9 ]
let evenDigits : Set = [2, 4, 6, 8]
let primeDigits : Set = [2, 3, 5, 7]

oddDigits.intersect(evenDigits).sort()

oddDigits.exclusiveOr(primeDigits).sort()

oddDigits.union(evenDigits).sort()

oddDigits.subtract(primeDigits).sort()

/*
 isSubsetOf(_:) : 집합이 파라미터의 부분집합인지 True, False로 리턴
 isSupersetOf(_:) : 집합이 파라미터의 상위집합인지 True, False로 리턴
 isStrictSubsetOf(_:) : 집합이 파라미터의 부분집합인지 True, False로 리턴. 단, 파라미터와 같은 집합일 경우 False리턴
 isStrictSupersetOf(_:) : 집합이 파라미터의 상위집합인지 True, False로 리턴. 단, 파라미터와 같은 집합일 경우 False리턴
 isDisjointWith(_:) : 집합이 파라미터와 교집합이 없을 때 True를 리턴. 교집합이 있으면 False를 리턴.
 */
//: ## Dictionary
var airports: [String: String] = ["YYZ": "Toronto Pearson", "DUB": "Dublin"]

print("The airports dictionary contains \(airports.count) items.")

if airports.isEmpty {
    print("The airports dictionary is empty.")
} else {
    print("The airports dictionary is not empty.")
}
//: * 걍 update 혹은 insert
airports["LHR"] = "London"

//: * oldValue 찾아주고 update
if let oldValue = airports.updateValue("Dublin Airport", forKey: "DUB") {
    print("The old value for DUB was \(oldValue).")
}
//: * remove
airports["APL"] = nil

//: * remove인데 oldValue 찾아주기
if let removedValue = airports.removeValueForKey("DUB") {
    print("The removed airport's name is \(removedValue).")
} else {
    print("The airports dictionary does not contain a value for DUB.")
}
//: * iteration 1
for (airportCode, airportName) in airports {
    print("\(airportCode): \(airportName)")
}
//: * iteration 2
for airportCode in airports.keys {
    print("Airport code: \(airportCode)")
}
for airportName in airports.values {
    print("Airport name: \(airportName)")
}
//: [Next](@next)
