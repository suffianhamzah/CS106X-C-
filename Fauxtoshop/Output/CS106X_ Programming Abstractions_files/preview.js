$(document).ready(function() {
  $('.lecture-preview').click(function(e) {
    var lecture = e.target.getAttribute('data-lecture');
    $('#preview-modal-body').load('previews/preview-' + lecture + '.shtml', function () {
      $('#previewModal').modal();
    });
  });
});
