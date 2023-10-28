DB_FILE="student_db.txt";

create_db()
{
 touch "$DB_FILE"
 echo "Database created successfully"
 
}

insert_db()
{
 echo -n "Enter Roll No :- "
 read rn
 echo -n "Enter Name :- "
 read name
 echo -n "Enter Address :- "
 read address
 echo -n "Enter marks of subject 1 :- "
 read m1
 echo -n "Enter marks of subject 2 :- "
 read m2
 echo -n "Enter marks of subject 3 :- "
 read m3
 
 echo "$rn,$name,$address,$m1,$m2,$m3" >> "$DB_FILE"
 echo "Student data inserted successfully."
}

display_db()
{
  echo "Student data: "
  cat "$DB_FILE"
}

delete_db()
{
  echo -n "Enter Roll No to be deleted "
  read rn
  if grep -q "$rn" "$DB_FILE"; then 
   sed -i "/$rn/d" "$DB_FILE"
   echo "Student with Roll No $rn deleted"
  else 
   echo "Student not found" 
  fi 
  
}

modify_db()
{
  echo -n "Enter Roll No to be modify "
  read rn
  if grep -q "$rn" "$DB_FILE"; then
     echo -n "Enter Roll No :- "
     read rn
     echo -n "Enter Name :- "
     read name
     echo -n "Enter Address :- "
     read address
     echo -n "Enter marks of subject 1 :- "
     read m1
     echo -n "Enter marks of subject 2 :- "
     read m2
     echo -n "Enter marks of subject 3 :- "
     read m3
 
     sed -i "s/^$rn,.*/$rn,$name,$address,$m1,$m2,$m3/" "$DB_FILE"
     echo "Student with Roll No $rn deleted successfully"
  else 
     echo "Student not found"
  fi      
   
}



while true; do
   echo "
   Student database mangement system
   1) Create database
   2) Insert record
   3) Display record
   4) Delete record
   5) Modify record
   6) Calculate avarage
   7) Exit
   "
   echo -n "Enter choice from 1-7: "
   read choice
   case $choice in 
       1)create_db  ;;
       2)insert_db  ;;
       3)display_db ;;
       4)delete_db  ;;
       5)modify_db  ;;
       6)calculate_avg ;;
       7)echo "Exiting" ; exit;;
       *)echo "Please enter valid option";;
    esac   
done

