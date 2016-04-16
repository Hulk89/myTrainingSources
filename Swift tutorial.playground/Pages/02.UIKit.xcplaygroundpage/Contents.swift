//: [Previous](@previous)
/*:
 ## UIKit을 import해서 결과를 보자!
 다음과 같은 코드를 짜보고 옆의 결과를 눈으로 볼 수 있다!
 */
import UIKit

let myLabel = UILabel(frame: CGRectMake(0, 0, 200, 50))
myLabel.backgroundColor = UIColor.redColor()
myLabel.text = "Hello Swift"
myLabel.textAlignment = .Center
myLabel.font = UIFont(name: "Georgia", size: 24)
myLabel

/*:
 ## Image를 Resource에 넣고 불러올 수도 있다!
 */
let image = UIImage(named: "drone.jpg")
//: [Next](@next)
