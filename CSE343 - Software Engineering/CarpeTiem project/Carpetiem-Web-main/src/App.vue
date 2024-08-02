<template>
  <div class="d-flex flex-column" style="height: 100vh">
    <nav
      class="navbar navbar-expand-md navbar-dark"
      style="background-color: #24252a"
    >
      <div class="container-fluid mx-md-5">
        <button
          class="navbar-toggler"
          type="button"
          data-bs-toggle="collapse"
          data-bs-target="#navmenu"
          @click="show_buttons = !show_buttons"
        >
          <span class="navbar-toggler-icon"></span>
        </button>
        <router-link :to="{ name: 'Home' }" class="navbar-brand me-0 me-sm-3">
          Carpetiem
        </router-link>
        <div class="collapse navbar-collapse ms-5" id="navmenu">
          <ul class="navbar-nav mx-auto">
            <li class="nav-item">
              <router-link :to="{ name: 'About' }" class="nav-link">
                Hakkımızda
              </router-link>
            </li>
            <li class="nav-item" v-if="user_type != 'firm'">
              <router-link
                :to="{ name: 'Firms', params: { page: 1 } }"
                class="nav-link"
              >
                Firmalar
              </router-link>
            </li>
          </ul>
        </div>
        <transition name="fade">
          <div :class="{ 'me-sm-5': logged_in }" v-if="show_buttons">
            <ul class="navbar-nav list-group d-flex flex-row">
              <li class="nav-item dropdown mx-2" v-if="logged_in">
                <Suspense>
                  <template #default>
                    <Dropdown
                      :uid="user_uid"
                      :user_type="user_type"
                      :logout="logout"
                    />
                  </template>
                  <template #fallback>
                    <DropdownSkeleton />
                  </template>
                </Suspense>
              </li>
              <li class="nav-item mx-2 d-none d-sm-block" v-if="!logged_in">
                <router-link class="btn" :to="{ name: 'Login' }">
                  Giriş Yap
                </router-link>
              </li>
              <li class="nav-item mx-2 d-none d-sm-block" v-if="!logged_in">
                <router-link class="btn" :to="{ name: 'Register' }">
                  Kaydol
                </router-link>
              </li>
            </ul>
          </div>
        </transition>
      </div>
    </nav>
    <router-view />
  </div>
</template>

<script>
import { ref } from "@vue/reactivity";
import { useRouter } from "vue-router";
import firebase from "firebase/compat/app";
import "firebase/compat/auth";
import Dropdown from "./components/Dropdown.vue";
import DropdownSkeleton from "./components/DropdownSkeleton.vue";

const registered_type = ref("none");
export const registered = (type) => {
  registered_type.value = type;
};

export const admin_uid = ref("");

export default {
  name: "App",
  components: { Dropdown, DropdownSkeleton },
  setup() {
    const show_buttons = ref(true);
    const router = useRouter();
    const logged_in = ref(false);
    const user_type = ref("none");
    const user_uid = ref("");

    firebase.auth().onAuthStateChanged((user) => {
      logged_in.value = !!user;
      user_type.value = !!user
        ? registered_type.value == "none"
          ? user.displayName
          : registered_type.value
        : "none";
      user_uid.value = !!user ? user.uid : "none";
      admin_uid.value = user_type.value == "firm" ? user.uid : "";
    });

    const logout = () => {
      firebase.auth().signOut();
      router.replace("/login");
    };

    return {
      logged_in,
      show_buttons,
      logout,
      user_type,
      user_uid,
    };
  },
};

/*.form-control:has(+ span):focus {
  box-shadow: 0 0 0 0.25rem red !important;
  clip-path: inset(-0.25rem 0rem -0.25rem -0.25rem);
}*/
</script>

<style scoped>
.btn {
  background-color: rgb(120, 150, 120);
  border: rgb(120, 150, 120);
}

.btn:hover {
  filter: brightness(85%);
}

.btn:focus {
  box-shadow: 0 0 0 0.25rem rgb(120 150 120 / 25%);
}
</style>

<style>
.button-container {
  flex-grow: 0.1;
}

.navbar-dark .navbar-nav .nav-link:hover {
  color: rgb(120, 150, 120);
}

.navbar-dark .navbar-toggler {
  color: rgb(120, 150, 120);
}

a:not(.btn) {
  color: rgb(120, 150, 120);
}

a:not(.btn):hover {
  filter: brightness(85%);
}

.navbar-dark .navbar-nav .btn:focus {
  box-shadow: none;
}

.dropdown-menu-dark .dropdown-item:active {
  color: #fff;
  background-color: rgba(120, 150, 120, 0.7);
}

.fade-enter-active,
.fade-leave-active {
  transition: opacity 0s ease;
}

.fade-enter-active {
  transition-delay: 0.35s;
}

.fade-enter-from,
.fade-leave-to {
  opacity: 0;
}

.btn-close:focus,
.form-select:focus,
.form-control:focus,
.form-check-input:focus,
.page-link:focus,
.page-link:hover {
  box-shadow: 0 0 0 0.25rem rgb(120 150 120 / 25%);
}

.form-select:focus,
.form-control:focus,
.form-control:focus + span {
  border-color: rgb(120, 150, 120);
}

.form-control + span {
  transition: border-color 0.35s;
}

.page-link:focus,
.page-link:hover {
  color: hsl(120, 12.5%, 45%);
}

.skeleton {
  opacity: 0.8;
  animation: skeleton-loading 1s linear infinite alternate;
}

@keyframes skeleton-loading {
  0% {
    background-color: hsl(200, 20%, 45%);
    color: hsl(200, 20%, 45%);
  }
  100% {
    background-color: hsl(200, 20%, 95%);
    color: hsl(200, 20%, 95%);
  }
}

html {
  scroll-behavior: smooth;
}
</style>
