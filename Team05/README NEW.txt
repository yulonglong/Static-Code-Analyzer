README NEW

Resubmission after evaluation

Team 05:
- A0099214B	Adinda Ayu Savitri	
- A0098139R	Hisyam Nursaid Indrakesuma
- A0103494J	Lacie Fan Yuxin	
- A0101286N	Ipsita Mohapatra	
- A0080415N	Steven Kester Yuwono	
- A0099768Y	Yohanes Lim	

The files included in this archive:
- Code05 		Folder contains our Visual Studio solution (source files).
- Tests05 		Folder contains our THREE test files (including combinations of clauses)
- UnitTests05	Folder contains our CodeParser and DesignExtractor files for Unit Testing
- Team05.pdf 	is the Final Report for this project

Information to build the system and unit testing are identical in the original README.txt

Bugs fixed:

1. line numbers 0, 63, 126, 252  missing from the answer. 
   It is caused by a bug in PKB with regards to its bitvector implementation. (the error always a multiple of 63, the size of the data type)
   Fixed by Yohanes Lim.
   
2. line numbers 280+ missing from the answer.
   It is caused by a bug in Design Extractor by not setting the call graph/table properly if other procedure is disjoint.
   Fixed by Ipsita.
   
3. Follows wild card wrong answer. E.g. (Follows (_,a))
   It is caused by a bug in Query Evaluator.
   Fixed by Lacie Fan Yuxin.

4. Pattern wrong answer. E.g. (pattern a("height", "tmp - k + I")).
   It is caused by a bug in Query Parser, detecting the query as invalid.
   Fixed by Steven Kester.

5. Affects with same argument exception. E.g. (Affects(a,a))
   It is caused by a bug in Query Evaluator "affects".
   Fixed by Hisyam Nursaid.

   
Note to Prof. Stan: 
- Source Code Parser is actually working perfectly and it does have error output if it crashes or encountered any invalid situation.
- It will try to catch an exception too whenever it happens.
- What we tried to explain during the presentation is that the Code Parser will not print any error in the case of uncaught exception or 
special corner cases when the invalid source code somehow passes all the validations.