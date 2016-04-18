//: [Previous](@previous)

//: ## Extensions
//: 기존의 class의 subclass를 만들지 말고 기능을 추가하고 싶을 때!

extension Double {
    
    var squared: Double {
        return self * self
    }
    
    var cubed: Double {
        return self * self * self
    }
}

var A : Double = 12.2

A.squared
A.cubed

//: [Next](@next)
