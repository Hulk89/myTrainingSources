from mock import Mock
 
# prepare the spec list
fooSpec = ["_fooValue", "callFoo", "doFoo"]
 
# create the mock object
mockFoo = Mock(spec = fooSpec)
 
# accessing the mocked attributes
print mockFoo
# <Mock id='427280'>
print mockFoo._fooValue
# returns <Mock name='mock._fooValue' id='2788112'>
print mockFoo.callFoo()
# returns: <Mock name='mock.callFoo()' id='2815376'>
 
mockFoo.callFoo()
# nothing happens, which is fine
 
# accessing the missing attributes
print mockFoo._fooBar
# raises: AttributeError: Mock object has no attribute '_fooBar'
mockFoo.callFoobar()
# raises: AttributeError: Mock object has no attribute 'callFoobar