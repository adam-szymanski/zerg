
namespace Ummon {
  
#define assertNotNull(a)\
  if ((a) == nullptr) {\
	  std::cout << "Assert failed: " << #a << " is not null failed at " << __FILE__ << ":" << __LINE__ << std::endl;\
	  *((int*)NULL) = 1;\
  }

#define assertIsTrue(a)\
  if (!(a)) {\
	  std::cout << "Assert failed: " << #a << " is true failed at " << __FILE__ << ":" << __LINE__ << std::endl;\
	  *((int*)NULL) = 1;\
  }

#define assertIsEqual(a, b)\
  if ((a) != (b)) {\
	  std::cout << "Assert failed: " << #a << " == " << #b << " failed at " << __FILE__ << ":" << __LINE__ << std::endl;\
    std::cout << #a << " = " << (a) << std::endl << #b << " = " << (b) << std::endl;\
	  *((int*)NULL) = 1;\
  }

#define assertNotEqual(a, b)\
  if ((a) == (b)) {\
	  std::cout << "Assert failed: " << #a << " != " << #b << " failed at " << __FILE__ << ":" << __LINE__ << std::endl;\
    std::cout << #a << " = " << (a) << std::endl << #b << " = " << (b) << std::endl;\
	  *((int*)NULL) = 1;\
  }

#define assertIsGreater(a, b)\
  if ((a) <= (b)) {\
	  std::cout << "Assert failed: " << #a << " > " << #b << " failed at " << __FILE__ << ":" << __LINE__ << std::endl;\
    std::cout << #a << " = " << (a) << std::endl << #b << " = " << (b) << std::endl;\
	  *((int*)NULL) = 1;\
  }

#define assertIsGreaterOrEqual(a, b)\
  if ((a) < (b)) {\
	  std::cout << "Assert failed: " << #a << " >= " << #b << " failed at " << __FILE__ << ":" << __LINE__ << std::endl;\
    std::cout << #a << " = " << (a) << std::endl << #b << " = " << (b) << std::endl;\
	  *((int*)NULL) = 1;\
  }

}; // namespace Ummon