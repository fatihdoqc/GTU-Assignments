import { createRouter, createWebHistory } from "vue-router";
import Home from "../views/Home.vue";
import About from "../views/About.vue";
import Login from "../views/Login.vue";
import Register from "../views/Register.vue";
import EmployeeSettings from "../views/EmployeeSettings.vue";
import Settings from "../views/Settings.vue";
import Firms from "../views/Firms.vue";
import AdminLogin from "../views/AdminLogin.vue";
import FirmRegister from "../views/FirmRegister.vue";
import NotFound from "../views/NotFound.vue";
import firebase from "firebase/compat/app";
import "firebase/compat/auth";
import OrderList from "../views/OrderList.vue";
import MyOrders from "../views/MyOrders.vue";

const routes = [
  {
    path: "/",
    name: "Home",
    component: Home,
  },
  {
    path: "/about",
    name: "About",
    component: About,
  },
  {
    path: "/login",
    name: "Login",
    component: Login,
    meta: { requiresUnauth: true },
  },
  {
    path: "/admin-login",
    name: "AdminLogin",
    component: AdminLogin,
    meta: { requiresUnauth: true },
  },
  {
    path: "/register",
    name: "Register",
    component: Register,
    meta: { requiresUnauth: true },
  },
  {
    path: "/firm-register",
    name: "FirmRegister",
    component: FirmRegister,
    meta: { requiresUnauth: true },
  },
  {
    path: "/employee-settings",
    name: "EmployeeSettings",
    component: EmployeeSettings,
    meta: { requiresAuth: true, requiresAdmin: true },
  },
  {
    path: "/settings",
    name: "Settings",
    component: Settings,
    meta: { requiresAuth: true, requiresCustomer: true },
  },
  {
    path: "/firms/page=:page",
    name: "Firms",
    component: Firms,
  },
  {
    path: "/myorders",
    name: "MyOrders",
    component: MyOrders,
  },
  {
    path: "/firms",
    redirect: { name: "Firms", params: { page: 1 } },
  },
  {
    path: "/orderlist",
    name: "OrderList",
    component: OrderList,
    meta: { requiresAuth: true, requiresAdmin: true },
  },
  {
    path: "/:catchAll(.*)",
    name: "NotFound",
    component: NotFound,
  },
];

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes,
});

router.beforeEach(async (to, from, next) => {
  const isAuth = firebase.auth().currentUser;
  const isAdmin = isAuth
    ? isAuth.displayName == "firm"
      ? true
      : false
    : false;
  const isCustomer = isAuth
    ? isAuth.displayName == "customer"
      ? true
      : false
    : false;
  const requiresAuth = to.matched.some((record) => record.meta.requiresAuth);
  const requiresUnauth = to.matched.some(
    (record) => record.meta.requiresUnauth
  );
  const requiresAdmin = to.matched.some((record) => record.meta.requiresAdmin);
  const requiresCustomer = to.matched.some(
    (record) => record.meta.requiresCustomer
  );

  if (requiresAuth && !isAuth) next("/login");
  else if (requiresAdmin && !isAdmin) next("/");
  else if (requiresCustomer && !isCustomer) next("/");
  else if (requiresUnauth && isAuth) next("/");
  else next();
});

export default router;
