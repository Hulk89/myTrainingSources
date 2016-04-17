//: [Previous](@previous)

/*:
 ## Functions
 */

//: ### 인자가 존재하지 않는 간단한 함수
func sayHello() {
    print("Hello")
}

sayHello()

//: ### 인자를 받아서 string을 return 하는 함수
func buildMessage(name: String, count: Int) -> String {
    return("\(name), you are customer number \(count)")
}

var string = buildMessage("GG", count: 1)

//: ### External parameter names
func sayHello2(to person: String, and anotherPerson: String) -> String {
    return "Hello \(person) and \(anotherPerson)!"
}
print(sayHello2(to: "Bill", and: "Ted"))
//: ### Default Parameter
func someFunction(parameterWithDefault: Int = 12) -> Int {
    return parameterWithDefault * 2
}
someFunction(6) // parameterWithDefault is 6
someFunction() // parameterWithDefault is 12

//: ### Variadic parameters
func arithmeticMean(numbers: Double...) -> Double {
    var total: Double = 0
    for number in numbers {
        total += number
    }
    return total / Double(numbers.count)
}
arithmeticMean(1, 2, 3, 4, 5)
arithmeticMean(3, 8.25, 18.75)


//: [Next](@next)
