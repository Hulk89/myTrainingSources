import cPickle
import numpy as np

def mergeAll(*dict_args):
    result = {"labels": [], "data": [] }
    
    for dictionary in dict_args:
    	if len( result['labels'] ) == 0 :
    		result['labels'] = dictionary['labels'] 
        	result['data']   = dictionary['data']
        else:
        	result['labels'] = np.append( result['labels'], dictionary['labels'],axis = 0  )
        	result['data'] = np.append( result['data'], dictionary['data'], axis = 0 )
    return result

def unpickle(file):
    fo = open(file, 'rb')
    dict = cPickle.load(fo)
    fo.close()
    return dict

def load_CIFAR():
	sDataList1 = unpickle( "cifar-10/data_batch_1" )
	sDataList2 = unpickle( "cifar-10/data_batch_2" )
	sDataList3 = unpickle( "cifar-10/data_batch_3" )
	sDataList4 = unpickle( "cifar-10/data_batch_4" )
	sDataList5 = unpickle( "cifar-10/data_batch_5" )

	sDataList = mergeAll( sDataList1, \
						  sDataList2, \
						  sDataList3, \
						  sDataList4, \
					   	  sDataList5 )
	sTestList = unpickle( "cifar-10/test_batch" )

	sDataList['data'] = np.reshape(sDataList['data'], (sDataList['data'].shape[0], 32, 32, 3) )
	sTestList['data'] = np.reshape(sTestList['data'], ( sTestList['data'].shape[0], 32, 32, 3) )

	sLabels = unpickle( "cifar-10/batches.meta" )
	sLabelNames =  sLabels['label_names']

	return sDataList['data'], sDataList['labels'], sTestList['data'], sTestList['labels'], sLabelNames
