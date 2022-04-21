<template>
  <div class="container d-flex flex-column flex-grow-1 justify-content-center">
    <h1 class="row justify-content-center">Carpetiem</h1>
  </div>
</template>

<script>
import db, { functions } from "../firebase";
import { ref } from "@vue/reactivity";
import firebase from "firebase/compat/app";
import "firebase/compat/auth";
import "firebase/compat/functions";
export default {
  name: "Home",
  components: {},
  setup() {
    const users = ref([]);
    const show = ref(false);

    /*var today = new Date();
    console.log(today.toLocaleString("tr-TR", { weekday: "long" }));
    console.log(today.getHours(), today.getMinutes());
    console.log(today.getTime());*/

    return {
      users,
      show,
    };
  },
};
</script>

<style scoped>
.btn {
  background-color: rgb(120, 150, 120);
  border: rgb(120, 150, 120);
}

.btn:hover {
  filter: brightness(85%);
}
</style>
