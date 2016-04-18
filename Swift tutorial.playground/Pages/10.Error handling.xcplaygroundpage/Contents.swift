//: [Previous](@previous)

enum ChangeError: ErrorType {
    case Empty
    case NotCode(code: Int)
}

func canThrowErrors(number : Int) throws -> String
{
    switch number
    {
    case 0:
        throw ChangeError.Empty
    case 1...10:
        throw ChangeError.NotCode(code: number)
    default:
        break
    }
    return "GG"
}

do {
    var str1 = try canThrowErrors(20)
    print( str1 )
    var str2 = try canThrowErrors(1)
    var str3 = try canThrowErrors(2)
} catch ChangeError.Empty {
    print("Empty!")
} catch ChangeError.NotCode(let code )
{
    print(code)
}



//: [Next](@next)
