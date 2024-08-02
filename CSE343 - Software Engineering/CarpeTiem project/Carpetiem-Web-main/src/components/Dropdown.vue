<template>
  <button
    class="btn dropdown-toggle"
    id="user-dropdown"
    role="button"
    data-bs-toggle="dropdown"
    aria-expanded="false"
    type="button"
  >
    {{ user_name }}
  </button>
  <ul
    class="dropdown-menu dropdown-menu-dark position-absolute"
    aria-labelledby="user-dropdown"
  >
    <li v-if="user_type == 'customer'">
      <router-link class="dropdown-item" :to=" { name: 'MyOrders' }"> Siparişlerim </router-link>
    </li>
    <li v-if="user_type == 'customer'">
      <router-link class="dropdown-item" :to="{ name: 'Settings' }">
        Profil Ayarları
      </router-link>
    </li>
    <li v-if="user_type == 'firm'">
      <router-link class="dropdown-item" :to="{ name: 'EmployeeSettings' }"
        >Personel Listesi</router-link
      >
    </li>
    <li v-if="user_type == 'firm'">
      <router-link class="dropdown-item" :to="{ name: 'OrderList' }"
        >Sipariş Listesi</router-link
      >
    </li>
    
    <li>
      <div class="dropdown-item" @click="logout" style="cursor: pointer">
        Çıkış
      </div>
    </li>
  </ul>
</template>

<script>
import db from "../firebase";
import { ref } from "@vue/reactivity";
export default {
  props: {
    uid: String,
    user_type: String,
    logout: Function,
  },
  async setup(props) {
    const user_name = ref(
      await db
        .collection(props.user_type + "s")
        .doc(props.uid)
        .get()
    );

    user_name.value = user_name.value.data().name;

    return {
      user_name,
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
