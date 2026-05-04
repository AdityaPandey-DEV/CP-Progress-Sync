CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  RETURN (
     select DISTINCT salary from (select salary , dense_rank() over (ORDER BY salary DESC) as rnk from Employee) as t where rnk = N
  );
END