# Test Cases for Money-to-Words Conversion

This file contains test cases for verifying the `money_to_words` function.

## 📝 **Test 1: Basic Cases**
| Input (cents) | Expected Output |
| `100`  `"one dollars and zero cents"` |
| `12345` `"one hundred twenty-three dollars and forty-five cents"` |
| `0`  `"zero dollars and zero cents"` |

## 📝 **Test 2: Edge Cases**
| Input (cents) | Expected Output |
| `1`  `"zero dollars and one cents"` |
| `999` `"nine dollars and ninety-nine cents"` |
| `100000`  `"one thousand dollars and zero cents"` |

## 📝 **Test 3: Large Numbers**
| Input (cents) | Expected Output |
| `149999`  `"one thousand four hundred ninety-nine dollars and ninety-nine cents"` |

