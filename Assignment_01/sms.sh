DB_FILE="db.txt";

insert_db()
{
 echo "Enter roll no: "
 read rn
 echo "Enter name: "
 read name
 echo "Enter address: "
 read addr
 echo "Enter marks of subject 1"
 read marks1
 echo "Enter marks of subject 2"
 read marks2
 echo "Enter marks of subject 3"
 read marks3
 echo "$rn,$name,$addr,$marks1,$marks2,$marks3" >> "$DB_FILE"
}

calculate_avg()
{
  #echo "Enter roll no of student"
  #read rn
  #result=$(grep "^$rn," "$DB_FILE")

  #if [ -z "$result" ]; then
  #  echo "Student not found"
  #else
  #  IFS=',' read -r id name location mark1 mark2 mark3 <<< "$result"
  #  average=$(echo "scale=2; ($mark1 + $mark2 + $mark3) / 3" | bc)
  #  echo "Average marks for $name: $average"
  #fi
  echo "Enter roll no to search"
  read rn
  result=$(grep "^$rn," "$DB_FILE")
  
  if [ -z "$result" ]; then
    echo "Student not found"
  else
     IFS=',' read -r id name loaction m1 m2 m3 <<< "$result"
     average=$(echo "scale=2; ($m1+$m2+$m3)/3" | bc)
     echo "Average marks of $name :- $average"
  fi
}

display_db()
{
 echo -e "ROllNo,Name,Address,Marks1,Marks2,Marks3\n"
 cat "$DB_FILE"
}

delete_db()
{
 echo "enter a roll No to delete"
 read rn
 if grep -q "$rn" "$DB_FILE"; then
    sed -i "/$rn/d" "$DB_FILE"
    echo "Deleted successfully"
 else
    echo "Not found"
 fi
 
}

modify_db()
{
 echo "Enter Roll No to modify"
 read rn
 if grep -q "$rn" "$DB_FILE"; then
    echo "Enter name"
    read name
    echo "Enter blaa"
    read blaa
    sed -i "s/^$rn,.*/$rn,$name,$blaa/" "$DB_FILE"
    echo "Data modified successfully"
 else
    echo "Student not found in this record"   
 fi
}

create_db()
{
 touch "$DB_FILE"
 echo "Database created successfully"
}

search_db()
{
 echo "Enter roll no to search"
 read rn
 result=$(sed -n "/^$rn/p" "$DB_FILE")
 if [ -z "$result" ]; then
   echo "Student not found"
 else
   echo "$result"
 fi
  
}

while true; do
   echo "
   Please Choose an option
   1) Create
   2) Insert 
   3) Display
   4) Delete
   5) Modify
   6) Search
   7) Average
   8) Exit
   "
   echo -e "Enter a choice from 1-5:\n"
   read choice
   case $choice in
       1)create_db;;
       2)insert_db;;
       3)display_db;;
       4)delete_db;;
       5)modify_db;;
       6)search_db;;
       7)calculate_avg;;
       8)exit;;
       *)echo "Enter valid option";; 
   esac
done   
 
