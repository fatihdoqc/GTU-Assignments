import Mathlib.Algebra.BigOperators.Ring
import Mathlib.Data.Real.Basic

@[ext]
structure Point where
x : ℝ
y : ℝ

@[ext]
structure Polygon where
  boundary: List Point
  interior: List Point
  area : ℝ
  boundary_num : ℕ
  interior_num : ℕ

noncomputable def myPolygon : Polygon where
  boundary := [
    { x := 0, y := 3 },
    { x := 1, y := 4 },
    { x := 2, y := 4 },
    { x := 3, y := 4 },
    { x := 4, y := 2 },
    { x := 4, y := 1 },
    { x := 2, y := 0 },
    ]
  interior := [
    { x := 1, y := 2 },
    { x := 1, y := 3 },
    { x := 2, y := 1 },
    { x := 2, y := 2 },
    { x := 2, y := 3 },
    { x := 3, y := 1 },
    { x := 3, y := 2 },
    { x := 3, y := 3 },
  ]
  area := 10.5
  boundary_num := 7
  interior_num := 8


axiom euler_polyhedral_theorem (V E F : ℕ) : V - E + F = 2

example (a b : Point) (hx : a.x = b.x) (hy : a.y = b.y) : a = b := by
ext
repeat' assumption

def origin : Point where
  x := 0
  y := 0

def myPoint1 : Point where
  x := 2
  y := -1

def myPoint2 : Point where
  x := 2
  y := -1

namespace Point

def add (a b : Point ) : Point where

  x := a.x + b.x
  y := a.y + b.y


theorem add_x (a b : Point) : (a.add b).x = a.x + b.x := by
  rfl

protected theorem add_comm (a b : Point) : add a b = add b a := by
rw [add, add]
ext <;> dsimp
repeat' apply add_comm

example (a b : Point) : add a b = add b a := by simp [add, add_comm]

theorem Pick_s_Theorem (A f e e_b i b v : ℝ  )
(h_equal: e_b = b)
(h_area: A = (f-1) / 2)
(h_edge1 : (f-1)/2 = (2*(e-f) - e_b + 2)/2 )
(euler : e-f = v - 2)
(node_num : v = i + b)
 : A = i + (b/2) - 1 := by

rw [h_area , h_edge1, euler, h_equal, node_num]
ring

#check Pick_s_Theorem
