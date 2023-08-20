#pragma once

/* Check Null */
#define CheckNull(p)\
		{\
			if(p == NULL)\
				return ;\
		}

/* Check Null Result */
#define CheckNullResult(p, result)\
		{\
			if(p == NULL)\
				return result;\
		}

/* Check True */
#define CheckTrue(p)\
		{\
			if(p == true)\
				return;\
		}

/* Check True Result */
#define CheckTrueResult(p, result)\
		{\
			if(p == true)\
				return result;\
		}

/* Check False */
#define CheckFalse(p)\
		{\
			if(p == false)\
				return;\
		}

/* Check False Result */
#define CheckFalseResult(p, result)\
		{\
			if(p == false)\
				return result;\
		}
