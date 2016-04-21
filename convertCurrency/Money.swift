//
//  Model.swift
//  convertCurrency
//
//  Created by Hyeongseok.oh on 2016. 4. 22..
//  Copyright © 2016년 Hyeongseok.oh. All rights reserved.
//

import Foundation

enum Currency: Int {
    case USD = 0, KOR, JPY
    
    var ratio: Double {
        get {
            var sRatio : Double
            
            switch self {
            case .USD:
                sRatio = 1.0
            case .KOR:
                sRatio = 1200
            case .JPY:
                sRatio = 120
            }
            
            return sRatio
        }
    }
    
    var prefix : String {
        get {
            switch self {
            case .USD:
                return "$"
            case .KOR:
                return "₩"
            case .JPY:
                return "¥"
            }
        }
    }
}

class Money {
    
    var mMoneyUSD : Double = 0
    
    init( _ amount:Double, currency: Currency ) {
        mMoneyUSD = amount / currency.ratio
    }
    
    func getMoneyWithCurrency( currency: Currency ) -> String {
        return currency.prefix + "\(mMoneyUSD * currency.ratio)"
    }
}
