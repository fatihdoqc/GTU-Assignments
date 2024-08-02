<template>
  <div class="container d-flex flex-column justify-content-center flex-grow-1">
    <div class="row mt-3 mt-md-0 mx-3 mx-sm-0">
      <div
        class="
          d-grid
          mx-auto
          col-md-8 col-lg-6 col-xl-5
          rounded
          border
          py-3
          my-3
        "
        v-if="!additionalInfo"
      >
        <RegisterForm
          header="Firma Kaydı"
          user_type="firm"
          @openAdditional="additionalInfo = !additionalInfo"
        />
      </div>
      <div
        class="d-grid mx-auto col-md-8 col-lg-6 col-xl-5 rounded border py-3"
        v-if="additionalInfo"
      >
        <AdditionalInfo />
      </div>
    </div>
  </div>
</template>

<script>
import { ref } from "@vue/reactivity";
import RegisterForm from "../components/RegisterForm.vue";
import AdditionalInfo from "../components/AdditionalInfo.vue";
export default {
  name: "FirmRegister",
  components: { RegisterForm, AdditionalInfo },
  setup() {
    const additionalInfo = ref(true);

    return {
      additionalInfo,
    };
  },
};
</script>
