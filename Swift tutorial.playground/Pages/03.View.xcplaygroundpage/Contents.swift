//: [Previous](@previous)
import UIKit
import XCPlayground

let container = UIView(frame: CGRectMake(0,0,200,200))

XCPlaygroundPage.currentPage.liveView = container // 요 녀석이 있어야하는구만!!

container.backgroundColor = UIColor.whiteColor()
let square = UIView(frame: CGRectMake(50,50,100,100))
square.backgroundColor = UIColor.redColor()

container.addSubview(square)

UIView.animateWithDuration(5.0, animations: {
    square.backgroundColor = UIColor.blueColor()
    let rotation = CGAffineTransformMakeRotation(3.14/2)
    square.transform = rotation
    
})
//: [Next](@next)
