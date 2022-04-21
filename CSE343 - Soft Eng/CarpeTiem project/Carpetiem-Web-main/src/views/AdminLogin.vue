<template>
  <div class="container d-flex flex-column justify-content-center flex-grow-1">
    <div class="row mt-3 mt-md-0">
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
          header="Yönetici Girişi"
          placeholder="admin@admin.com"
          user_type="firm"
        />
      </div>
    </div>
  </div>
</template>

<script>
import LoginForm from "../components/LoginForm.vue";
export default {
  name: "AdminLogin",
  components: { LoginForm },
};
</script>
