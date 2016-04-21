//
//  ViewController.swift
//  convertCurrency
//
//  Created by Hyeongseok.oh on 2016. 4. 22..
//  Copyright © 2016년 Hyeongseok.oh. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var segmentedControl: UISegmentedControl!
    @IBOutlet weak var moneyField: UITextField!
    @IBOutlet weak var resultText: UITextView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBAction func convertTouched(sender: AnyObject) {
        guard let srcCurrency = Currency( rawValue: segmentedControl.selectedSegmentIndex ) else {
            print("segmentedIndex Error")
            return
        }
        guard let money = Double(moneyField.text!) else {
            print("NoMoney!!")
            return
        }
        
        let sMoney = Money( money, currency: srcCurrency )
        
        var text: String = ""
        for i in 0..<3
        {
            text += sMoney.getMoneyWithCurrency( Currency(rawValue: i)! )
            text += "\r\n"
        }
        resultText.text = text
        
    }

}

