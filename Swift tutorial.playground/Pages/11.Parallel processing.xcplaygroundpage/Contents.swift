//: [Previous](@previous)

import Foundation

//: ## GCD( Grand Central Dispatch )

//: GCD에서 Queue를 하나 가져오는데 우선순위가 기본인 queue를 가져와라!
let queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)

//: queue에다가 클로져를 굴려라!
dispatch_async( queue, { ()->() in
    var result = 0
    for i in 1...10 {
        result += i
        sleep(1)
    }
    dispatch_async( dispatch_get_main_queue(), { ()->() in
        print("Result = \(result)")
        result
        sleep(10)
    })
} )

print( "이게 더 먼저 실행될껄?")
sleep(200)
//: [Next](@next)
