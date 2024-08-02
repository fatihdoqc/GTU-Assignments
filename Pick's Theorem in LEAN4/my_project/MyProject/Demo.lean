import Mathlib.Algebra.BigOperators.Ring
import Mathlib.Data.Real.Basic

theorem Pick_s_Theorem (A f e e_b i b v : ℝ  )
(h_equal: e_b = b)
(h_area: A = (f-1) / 2)
(h_edge1 : (f-1)/2 = (2*(e-f) - e_b + 2)/2 )
(node_num : v = i + b)
(euler : e-f = v - 2)
 : A = i + (b/2) - 1 := by

rw [h_area, h_edge1, euler, h_equal, node_num]
ring
