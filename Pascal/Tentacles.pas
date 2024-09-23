//Программа "Щупальца". Порт с midletPascal :)

uses
  GraphABC;

const
  S = 6; // Кол-во щупалец
  N = 60;  // Кол-во звеньев в каждом из них
  W = 1; //Ширина щупалец

var
  i, j, h: Integer;
  x, y: Real;
  tx, ty: Real;
  k, d: Real;
  r, g, b, f: byte;
  
  // Углы поворота звеньев относительно друг-друга
  a: array [1..N] of Real;
  
  // Длина одного звена
  len: Real;

procedure KeyDown(Key: integer);
begin
  case Key of
    VK_Left: k := 3 * pi / 2;
    VK_Right: k := pi / 2;
    VK_Up: k := 0;
  end;
end;


begin
  Pen.Width := W;
  SetWindowSize(320, 320);
  maximizewindow;
  SetWindowTitle('Щупальца');
  SETBRUSHCOLOR(CLBLACK);
  OnKeyDown := KeyDown;
  
  if Window.Width > Window.Height then
    len := Window.Height / 1.8 / N
  else
    len := Window.Width / 1.8 / N;
  k := random(360) * pi / 180;
  d := pi * 2 / S;
  
  var k1 := 1;
  
  // Главный цикл
  repeat
    
    if Window.Width > Window.Height then
      len := Window.Height / 1.8 / N
    else
      len := Window.Width / 1.8 / N;
    
    LockDrawing(); //Блокируем рисование(для оптимизации)
    ClearWindow(ClBlack); // Стираем всё
    
    // Расчёт коэфицента поворота
    if random(50) = 0 then
      k := random(360) * pi / 180;
    
    // Поворот всех щупалец
    a[1] := a[1] + sin(k) / 15;
    
    // Интерполяция углов между щупальцами
    for i := 2 to N do 
      a[i] := a[i] + (a[i - 1] - a[i]) * 0.1;
    if (random(41) = 37) then
      h := random(0, 2);
    for j := 0 to S - 1 do
    begin
      x := 0.5 * Window.Width;
      y := 0.5 * Window.Height;
      for i := 2 to N do 
      begin
        SetPenColor(Color.FromArgb(r, (trunc(255 - 255 * i / n) + g) mod 255, 255 - b));
        
        // Немного школьной тригонометрии :)           
        tx := x + cos(j * d + a[i]) * len;
        ty := y + sin(j * d + a[i]) * len;
        case h of
          0: Line(trunc(x), trunc(y), trunc(tx), trunc(ty));
          1: circle(trunc(x), trunc(y), 1);
          2:
            begin
              Line(trunc(x), trunc(y), trunc(tx), trunc(ty));
              Rectangle(trunc(x), trunc(y), trunc(tx), trunc(ty));
            end;
        end;//}
        //Line(trunc(x), trunc(y), trunc(tx), trunc(ty));
        //circle(trunc(x), trunc(y), 1);
        //Rectangle(trunc(x), trunc(y), trunc(tx), trunc(ty));
        x := tx;
        y := ty;
      end;
    end;
    Redraw(); //Перерисуем изображение
    
    k1 += 1;
    SetWindowTitle('Щупальца( Средн. FPS ' + Format('{0,5:f2}', k1 / Milliseconds * 1000) + ')');
    r += random(0, 2);
    g += random(0, 2);
    b += random(0, 2);
    f += random(0, 4);
    //sleep(5);
  until false;
  
end.
