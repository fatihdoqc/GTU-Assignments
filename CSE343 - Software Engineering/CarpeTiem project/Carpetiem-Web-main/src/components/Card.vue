<template>
  <div class="card mx-3 mt-3" style="max-width: 540px">
    <div class="row g-0">
      <div class="col-sm-4">
        <img :src="imageUrl" class="img-fluid rounded-start w-100" />
      </div>
      <div class="col-sm-8">
        <div class="card-body">
          <h5 class="card-title">Card title</h5>
          <p class="card-text">
            This is a wider card with supporting text below as a natural lead-in
            to additional content. This content is a little bit longer.
          </p>
          <p class="card-text">
            <small class="text-muted">Gebze Teknik Üniversitesi, Kocaeli</small>
          </p>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  props: {
    uid: String,
    imageUrl: String,
  },
  setup(props) {
    //const
  },
};
</script>

<style></style>
