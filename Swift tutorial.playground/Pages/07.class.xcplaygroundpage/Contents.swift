//: [Previous](@previous)

//: ## Class

/*
class NewClassName: ParentClass {
    // Properties
    // Instance Methods
    // Type methods
}
*/

class BankAccount {
    var accountBalance: Float = 0
    var accountNumber: Int = 0
    
    init(number: Int, balance: Float) // initializer
    {
        accountNumber = number
        accountBalance = balance
    }
    
    init()
    {
        accountNumber = 0
        accountBalance = 0
    }
    deinit                          //deinitialize method
    {
        
    }
    func displayBalance()
    {
        print("Number \(accountNumber)")
        print("Current balance is \(accountBalance)")
    }
    
    class func getMaxBalance() -> Float // class Method
    {
        return 100000.00
    }
}

var account1 = BankAccount(number: 12312312, balance: 400.54)
var account2 = BankAccount()
BankAccount.getMaxBalance()

//: [Next](@next)
