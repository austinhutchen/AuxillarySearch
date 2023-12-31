<h1>
<b>
OBSERVATIONS:
</h1>
</b>
<ul>
<li> 
By my tests using both chaining and open addressing collision resolution methods to bulk insert and search from files, it appears that chaining is quicker, because of the ability to be assured that your search will start at an index and cover the size of a linked list in linear time. In the case of quadratic probing and insertion, this formula  can span multiple runs of an entire hash table, before storing the desired element. This also complicates search, because it is not guranteed that your search only needs to check one index.
</li>
    
    
 <li>
Using the BST for both hashing mechanisms wasn't a bad decision, but alternatively, I could use a min/max heap and priority queue, sorted by the number of courses a given professor teaches. This would work well in theory because professors with more courses taught are more likely to be searched, as they are more popular.
</li>

<li>
I believe that I could improve this application by implementing an array doubling algorithm to double the hash table if the user inputs an insufficient size, until all of the data is inputted into the table. This would ensure proper data storage of larger files, where the number of lines in the file could be unknown. I would also improve the stringstream splitting to be more accurate for files formatted less neatly, for ex. finding a professorid without the aid of a specific delimiter.
</li>

</ul>