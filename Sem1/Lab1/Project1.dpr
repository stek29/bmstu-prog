program Project1;
{$APPTYPE CONSOLE}

Var A, B, C, D, X1, X2 : Single;

Begin
 	WriteLn('Input A, B, C:');
 	ReadLn(A, B, C);
 	A := 2 * A;  // Нам понадобится только 2*a
 	D := sqr(B) - 2 * A * C;
 	if D >= 0 then begin
    	// Первоначальное значение b нужно только для вычисления дискриминанта
    	// Далее понадобится только b/2a
    	B := -B / A;
    	// Если D будет равно нулю, то x1 и x2 будут равны -b/2a
    	if D = 0 then begin
       	X1 := B;
       	X2 := B;
    	end else begin
       	D := sqrt(D) / A;
       	X1 := B + D;
       	X2 := B - D;
    	end;
    	WriteLn('X1 = ', X1:6:1);
    	WriteLn('X2 = ', X2:6:1);
 	end else
     		WriteLn('No result');
 	ReadLn;
End.

