<template>
  <div class="container d-flex flex-column justify-content-center flex-grow-1">
    <div class="row">
      <div
        class="
          d-grid
          mx-auto
          col-11 col-md-8 col-lg-6 col-xl-5
          rounded
          border
          py-3
        "
      >
        <LoginForm
          header="Kullanıcı Girişi"
          placeholder="example@example.com"
          user_type="customer"
        />
      </div>
    </div>
  </div>
</template>

<script>
import LoginForm from "../components/LoginForm.vue";
export default {
  name: "Login",
  components: { LoginForm },
};
</script>
